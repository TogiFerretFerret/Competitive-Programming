# using bs4/requests-html to extract text from HTML content (from a file)
from bs4 import BeautifulSoup
from requests_html import HTMLSession
# load p2.html
with open('p3.html', 'r', encoding='latin1') as file:
    html_content = file.read()
# parse with BeautifulSoup
soup = BeautifulSoup(html_content, 'html.parser')
# extract text
text = soup.get_text()
print(text)
