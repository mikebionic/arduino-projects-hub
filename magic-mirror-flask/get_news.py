from bs4 import BeautifulSoup
import requests
main_url = "https://turkmenportal.com/blog/novosti"
res= requests.get(main_url)
res.raise_for_status()
soup = BeautifulSoup(res.text,'html.parser')

time_tags = soup.find('time').get_text()
print (time_tags)
h4_tags = soup.find_all('h4')
h4_tags_text = [tag.get_text().strip() for tag in h4_tags]
# print (h4_tags_text[2:-6])
news_splitted = h4_tags_text[2:-6]

text_str = ', '.join(news_splitted)

def write_to_file(text):
    f= open("news_latest.txt","w+")
    f.write(text)
    f.close()

write_to_file(text_str)
