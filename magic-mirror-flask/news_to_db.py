from flask import Flask, flash, request, redirect, render_template, url_for
from flask_sqlalchemy import SQLAlchemy

from bs4 import BeautifulSoup
import requests
# from file_operations import write_to_file

app = Flask(__name__)
app.config['SECRET_KEY'] = 'zTctP8FjbAAmy4?NuM3u'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mirror.db'
db = SQLAlchemy(app)


class News(db.Model):
    id = db.Column('id', db.Integer, nullable = False, primary_key=True)
    news = db.Column('news', db.String, nullable = False)
    def __repr__(self):
        return "News({},{})".format(self.id,self.news)


main_url = "https://turkmenportal.com/tm/blog/tazelikler"
res= requests.get(main_url)
res.raise_for_status()
soup = BeautifulSoup(res.text,'html.parser')

time_tags = soup.find('time').get_text()
h4_tags = soup.find_all('h4')
h4_tags_text = [tag.get_text().strip() for tag in h4_tags]
news_splitted = h4_tags_text[2:-6]
text_str = ', '.join(news_splitted)
print(text_str)
news = text_str
try:
    updates = News(news=news)
    db.session.add(updates)
    db.session.commit()
except ValueError as ex:
    print("Exception caught:", ex)

