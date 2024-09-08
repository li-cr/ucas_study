# _plugins/default_layout.rb
module Jekyll
    class DefaultLayout < Jekyll::Generator
      safe true
      priority :low
  
      def generate(site)
        # 处理页面
        site.pages.each do |page|
          if page.extname == '.md' && page.data['layout'].nil?
            page.data['layout'] = 'post'
            puts "Set layout 'post' for page: #{page.path}"  # 调试输出
          end
        end
  
        # 处理静态文件
        site.static_files.each do |file|
          if file.extname == '.md' && file.data['layout'].nil?
            file.data['layout'] = 'post'
            puts "Set layout 'post' for static file: #{file.path}"  # 调试输出
          end
        end
      end
    end
  end
  