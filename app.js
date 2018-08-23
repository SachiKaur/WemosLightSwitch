var express = require("express");
var request = require('request');
var nodemailer = require('nodemailer');
var app = express();

var transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
      user: 'YOUR_EMAIL',
      pass: 'PASSWORD'
    }
  });
  
function sendMessage(subject,message)
{
    var mailOptions = {
        from: 'FROM',
        to: 'TO',
        subject: subject,
        text: message,
    }

    transporter.sendMail(mailOptions, function(error, info){
        if (error) {
            console.log(error);
        } else {
            console.log('Email sent: ' + info.response);
        }
        });
}
  

app.get("/api/light/:id/:state", function(req, res) {
    var id = req.params.id;
    var state = req.params.state
    console.log(id + " " + state);

    if (id == 1){
        request('http://IP_ADDRESS/light?param='+state, function (error, response, body) {
            if (error) {
                res.json(error);
                sendMessage("Something went wrong with Light 1","Check the battery!");
            }
            else {
                res.json(body);
            }
        }); 
    }
});

app.listen(3000, function() {
  console.log("Example app listening on port " + 3000);
});