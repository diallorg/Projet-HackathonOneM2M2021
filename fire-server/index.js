const express = require('express');
const app = express();
const cors =  require('cors');
const mongoose = require('mongoose');
const config = require('./middleware/config')

// Body Parser Middleware and Cors
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cors());

// Set api routes
app.use('/sensor-instances', require('./routes/sensorInstance'));
// IN receivers
app.get("/", (req,res) => {
  console.log("Received get request on root.");
  console.log(req);
  res.send('Welcome to fire server. This is the root. You can type /fires for fires /hydrants for hydrants, /prevents for prevents and /sensor-instances for sensor instances.'); 
})
main();
async function main(){
  // Connect to dababase
  console.log("Connecting to database.");
  await mongoose.connect(config.mongoDBLink);

  app.listen(config.AEPort, function () {
    console.log(`Server started on port ${config.AEPort}.`);
  });
}




