require 'fileutils'

module Jekyll
  class GenerateHTMLForFiles < Jekyll::Generator
    priority :low

    def generate(site)
      base_directory = site.source
      output_directory = File.join(base_directory, "..", "_site")  # 指向 _site 的同级目录

      # 确保输出目录存在
      FileUtils.mkdir_p(output_directory)

      # 扫描目录及其子目录中的所有文件
      Dir.glob("#{base_directory}/**/*").reject { |f| File.directory?(f) }.each do |file_path|
        # 为每个文件在其同级目录中创建 HTML 文件
        create_html_for_file(file_path, base_directory)
      end
    end

    private

    def create_html_for_file(file_path, base_directory)
      file_name = File.basename(file_path, File.extname(file_path))
      file_extension = File.extname(file_path)
      relative_path = file_path.sub("#{base_directory}/", '')
      parent_dir = File.dirname(file_path)

      # 创建 HTML 文件内容
      html_content = <<~HTML
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">
          <title>File: #{file_name}</title>
        </head>
        <body>
          <h1>File: #{file_name}</h1>
          <p><a href="#{relative_path}">Download #{file_name}#{file_extension}</a></p>
        </body>
        </html>
      HTML

      # 创建 HTML 文件路径，在文件的同级目录中
      html_file_path = File.join(parent_dir, "#{file_name}.html")

      # 写入 HTML 文件
      File.write(html_file_path, html_content)
      puts "Created #{html_file_path}"  # 输出调试信息
    end
  end
end
