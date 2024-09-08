require 'fileutils'

module Jekyll
  class DirectoryPageGenerator < Jekyll::Generator
    priority :high

    def generate(site)
      # 扫描所有目录并生成 HTML 页面
      scan_directories(site.source).each do |dir|
        # 为每个目录生成一个 HTML 页面
        create_directory_page(site, dir[:path], dir[:files])
      end
    end

    private

    def scan_directories(root)
      entries = []

      # 扫描根目录下的文件
      root_dir_files = Dir.glob("#{root}/*").reject { |f| File.directory?(f) }
      root_files = root_dir_files.map do |file|
        {
          name: File.basename(file),
          path: file.sub("#{root}/", '')  # 去除根路径前缀
        }
      end
      entries << { path: '', files: root_files }  # 根目录的文件

      # 扫描子目录
      Dir.glob("#{root}/**/*").select { |f| File.directory?(f) }.each do |dir|
        relative_path = dir.sub("#{root}/", '')  # 获取相对路径
        next if ["_site", "_plugins", "_layouts"].any? { |exclude| relative_path.start_with?(exclude) }  # 排除指定目录
        files = Dir.glob("#{dir}/*").reject { |f| File.directory?(f) }.map do |file|
          {
            name: File.basename(file),
            path: file.sub("#{root}/", '')  # 去除根路径前缀
          }
        end
        entries << { path: relative_path, files: files }
      end

      entries
    end

    def create_directory_page(site, path, files)
      # 确保目录路径是相对路径
      dir_path = path.empty? ? 'index.html' : "#{path}/index.html"

      # 创建文件内容
      content = <<~HTML
        ---
        layout: default
        title: Directory Listing for #{path.empty? ? '/' : path}
        ---
        <h1>Directory Listing for #{path.empty? ? '/' : path}</h1>
        <ul>
          #{files.map { |file| "<li><a href='#{file[:path]}'>#{file[:name]}</a></li>" }.join("\n")}
        </ul>
      HTML

      # 将内容写入文件
      file_path = File.join(site.source, dir_path)
      FileUtils.mkdir_p(File.dirname(file_path))  # 确保目录存在
      File.write(file_path, content)

      # 使用 Jekyll::Document 类来处理 HTML 文件
      site.pages << Jekyll::Document.new(
        site,
        File.dirname(file_path),
        File.basename(file_path),
        content
      )
    end
  end
end
