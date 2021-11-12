const express = require('express');
const app = express();
const cors =  require('cors');
const mongoose = require('mongoose');
const discover = require('./middleware/discover');
const subscribe = require('./middleware/subscribe');
const config = require('./middleware/config')

// Body Parser Middleware and Cors
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cors());

// Set api routes
app.use('/fires', require('./routes/fires'));
app.use('/hydrants', require('./routes/hydrants'));
app.use('/prevents', require('./routes/prevents'));
app.use('/send/humidity', require('./routes/inReceivers/humidity'));
app.use('/send/flame', require('./routes/inReceivers/flame'));
app.use('/send/temperature', require('./routes/inReceivers/temperature'));
app.use('/send/windSpeed', require('./routes/inReceivers/windSpeed'));
app.get("/", (req,res) => {
  console.log("Received get request on root.");
  console.log(req);
  res.send('Welcome to fire server. This is the root. You can type /fires for fires /hydrants for hydrants and /prevents for prevents.'); 
})
main();
async function main(){
  // Connect to dababase
  console.log("Connecting to database.");
  await mongoose.connect(config.mongoDBLink);

  // Discover MNs and AEs
  await discover();
  app.listen(config.AEPort, function () {
    console.log(`Server started on port ${config.AEPort}.`);
  });
  
  await subscribe();
  
}




