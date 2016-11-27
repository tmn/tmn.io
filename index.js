const path = require('path')
const express = require('express')
const app = express()

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'js')

app.engine('js', require('express-react-views').createEngine({ beautify: true }))

app.use(express.static(path.join(__dirname, 'public')))

app.get('/', (req, res) => {
  res.render('index', { title: 'tmn.io' })
})

app.get('/is/professional', (req, res) => {
  res.render('cv')
})

app.get('/read/:article_name', (req, res) => {
  res.render('article', { title: 'tmn.io - ' + req.params.article_name, article: req.params.article_name })
})

app.listen(3000)

module.exports = app
