# hooks.py
import yaml

def build_toc(nav_list, level=1):
    html = ""
    for item in nav_list:
        if isinstance(item, dict):
            for title, value in item.items():
                html += f'<li class="toc-level-{level}"><span class="toc-item-title">{title}</span>'
                if isinstance(value, list):
                    html += f'\n<ul class="toc-sublist">\n'
                    html += build_toc(value, level + 1)
                    html += "</ul>\n"
                html += "</li>\n"
    return html

def on_page_markdown(markdown, page, config, files):
    if page.file.src_path == "toc.md":
        nav_data = config.get('nav', [])
        
        custom_html = '<div class="pdf-toc-container">\n<h1 class="toc-title">Table of Contents</h1>\n<ul class="toc-list">\n'
        custom_html += build_toc(nav_data, 3)
        custom_html += '</ul>\n</div>'
        
        return custom_html
    
    return markdown