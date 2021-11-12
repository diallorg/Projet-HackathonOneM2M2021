const config = {
  AEIp: "",// ip of this app, Set 192 local ip
  AEPort: 4000, // port of this app
  INIp: "127.0.0.1", // ip of the infrastructure node
  INIPort: 8080, // port of the infrastructure node
  sensors:["humidity","flame","windSpeed","temperature"], // containers of the AE, you need to handle them in inReceivers
  mongoDBLink:"mongodb+srv://iotiaUser:05pTDIzvApnxEF5G@cluster0.pcf53.mongodb.net/hephaestus?retryWrites=true&w=majority" // Link of your mongoDB Database
}

module.exports = config;
