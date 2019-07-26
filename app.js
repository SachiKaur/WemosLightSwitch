var express = require("express");
var app = express();
var firebase = require('firebase');
var config = require('./config.json');

firebase.initializeApp(config.FirebaseConfig);
var db= firebase.database();

app.get("/api/light/:id/:state", function(req, res) {
    var id = req.params.id;
    var state = req.params.state
    console.log(id + " " + state);

    if (id == 1){
        var ref = db.ref("wemosLightSwitch/one/commands");

        ref.push().set({
            time: firebase.database.ServerValue.TIMESTAMP,
            state: state
          });

    }
    res.send('Command added to the queue.')
});

app.listen(3000, function() {
  console.log("Example app listening on port " + 3000);
});