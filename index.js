var engines = require('consolidate')
var path = require('path')

var express = require('express')
var app = express()

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'html')

app.engine('html', engines.hogan)

app.use(express.static(path.join(__dirname, 'public')))

app.get('/', function (req, res) {
  res.render('index', { title: 'tmn.io',  partials: { header: 'header', footer: 'footer' } })
})

app.get('/is', function (req, res) {
  res.render('about', { title: 'tmn.io - about',  partials: { header: 'header', footer: 'footer' } })
})

app.get('/is/professional', function (req, res) {
  res.render('cv')
})

app.listen(3000)

module.exports = app
