module Jekyll
    class ListDirectories < Liquid::Tag
      def initialize(tag_name, text, tokens)
        super
        @text = text.strip
      end
  
      def render(context)
        site = context.registers[:site]
        base_url = site.config['baseurl'] || ''
        directories_and_files = scan_directories(site.source)
        
        directories_and_files.map do |entry|
          next if entry[:path].start_with?("_site", "_plugins", "_layouts")  # 排除指定目录
          "<h2>#{entry[:path]}</h2>" +
          "<ul>" +
          entry[:files].map do |file|
            "<li><a href='#{File.join(base_url, file[:path])}'>#{file[:name]}</a></li>"
          end.join + 
          "</ul>"
        end.join
      end
  
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
          files = Dir.glob("#{dir}/**/*").reject { |f| File.directory?(f) }.map do |file|
            {
              name: File.basename(file),
              path: file.sub("#{root}/", '')  # 去除根路径前缀
            }
          end
          entries << { path: relative_path, files: files }
        end
        
        entries
      end
    end
  end
  
  Liquid::Template.register_tag('list_directories', Jekyll::ListDirectories)