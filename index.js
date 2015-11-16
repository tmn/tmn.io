// var engines = require('consolidate')
var path = require('path')

var express = require('express')
var app = express()

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'js')

app.engine('js', require('express-react-views').createEngine({ beautify: true }))

app.use(express.static(path.join(__dirname, 'public')))

app.get('/', function (req, res) {
  res.render('index', { title: 'tmn.io' })
})

app.get('/is/professional', function (req, res) {
  res.render('cv')
})

app.get('/article/:article_name', function (req, res) {
  res.render('article', { title: 'tmn.io - ' + req.params.article_name, article: req.params.article_name })
})

app.listen(3000)

module.exports = app
