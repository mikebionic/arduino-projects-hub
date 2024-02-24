import datetime
from flask import Flask, flash, request, redirect, render_template, url_for
from flask_sqlalchemy import SQLAlchemy, inspect
import os
import get_from_file as cache

app = Flask(__name__)
app.config['SECRET_KEY'] = 'zTctP8FjbAAmy4?NuM3u'
# app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///data.db'
# db = SQLAlchemy(app)



@app.route('/', methods=['GET'])
def mirror():
	news = cache.get_text()
	return render_template('mirror.html', news=news)
	




if __name__ == "__main__":
	app.run(host="0.0.0.0" , port=5000 , debug=True)
	
