var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var cors = require('cors');
var fs = require('fs');

app.use('/public', express.static(__dirname + '/public'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:true}));
app.use(cors());


var serialport = require('serialport');
var portName = process.argv[2];

var myPort = new serialport(portName, {
    baudRate: 9600,
    parser: new serialport.parsers.Readline('\r\n')
});

myPort.on('open', onOpen);
myPort.on('data', onData);

function onOpen(){
    console.log('Open connections!');
}

function onData(data){
    console.log('on Data ' + data);
}

app.get('/', function(req,res){
  fs.readFile('./public/form.html', (err,html)=>{
    res.writeHead(200, {'Content-Type':'text/html; charset=EUC-KR'});
    res.end(html);
  });
})


app.post('/ajax_send_email', function(req, res){
  console.log(String(req.body.email));
  myPort.write(String(req.body.email));
  var responseData = {'result' : 'ok', 'email' : req.body.email}
  res.json(responseData);
  // 서버에서는 JSON.stringify 필요없음
})


app.listen(3000, function(){
  console.log("this line will be at the end");
})