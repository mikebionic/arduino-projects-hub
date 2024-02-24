# from flask_sqlalchemy import SQLAlchemy

# app.config['SECRET_KEY'] = 'zTctP8FjbAAmy4?NuM3u'
# app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mirror.db'
# db = SQLAlchemy(app)



class Weather(db.Model):
	id = db.Column('id', db.Integer, nullable= False, primary_key=True)
	state = db.Column('state', db.String, nullable = False)
	def __repr__(self):
		return f"Weather('{ self.id }','{ self.state }')"

class News(db.Model):
	id = db.Column('id', db.Integer, nullable = False, primary_key=True)
	news = db.Column('news', db.String, nullable = False)
	def __repr__(self):
		return f"News('{ self.id }','{ self.news }')"