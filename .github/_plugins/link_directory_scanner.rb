require 'win32ole'

module Jekyll
  class LinkDirectoryScanner < Jekyll::Generator
    priority :high

    def generate(site)
      # 扫描根目录下的.lnk文件
      root = site.source
      Dir.glob("#{root}/*.lnk").each do |lnk_file|
        target_path = resolve_link(lnk_file)
        if File.directory?(target_path)
          # 递归扫描.lnk文件指向的目录及其子目录
          add_directory_to_site(site, target_path, '')
        end
      end
    end

    private

    def resolve_link(file_path)
      shell = WIN32OLE.new('WScript.Shell')
      link = shell.CreateShortcut(file_path)
      link.TargetPath  # 返回快捷方式指向的路径
    end

    def add_directory_to_site(site, directory_path, relative_path)
      # 将目录及其内容加入到Jekyll的静态文件列表中
      Dir.glob("#{directory_path}/**/*").each do |file|
        next if File.directory?(file)
        file_relative_path = file.sub("#{directory_path}/", '')
        site.static_files << Jekyll::StaticFile.new(site, File.dirname(file), File.basename(file), File.read(file))
      end
    end
  end
end
