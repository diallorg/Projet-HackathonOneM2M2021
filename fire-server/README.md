# HEPHAESTUS PROJECT / Fire-server

## Description 
Hephaestus: is a forest fire prevention tool that serves the fire brigade by locating the different
areas of risk using temperature, wind, CO2, GPS and humidity sensors, allowing the firemen to take action
before a fire ignites.

## About this app
Backend server developed in NodeJS with ExpressJS, the app establishes the relation between the front-end VueJS client server and the Infrastructure Node.
It also permits to send a text message if a fire is detected.

## Prerequisites
Download nodeJS and npm.
Deploy a mongoDB database wherever you want.

## Start 
Infrastructure Node and MiddleNodes has to be started, Application Entities and containers created.

Clone this repo, go inside the folder,
set the configuration, see middleware/config.js,
run : "npm i && npm run start".

## What it does 
### Discovering
At launch, the app will look for all the Middle Nodes presents in the Infrastructure Node, and will store in a database :
  - The Middle Node,
  - His Application Entites,
  - His Containers.

See ./middleware/discover.js.

### Subscription
At launch, the app will subscribe to every container discovered previously according to all the sensors specified in middleware/config.js.

see ./middleware/subscribe.js.

Each sensor will be specified to post on each file they are supposed to in ./routes/inReceivers/.

### Listening
After having subscribed, the app will listen for each subscription sector as, humidity, temperature, wind and flame.
See ./routes/inReceivers.
After receiving a request, the app will store in the database the new event, depending on what kind of data is transmitted, there can be additional events (e.g send sms alert for fire).

In the other hand, the app keeps a relation between the database and the Vue.JS client.
The client will ask for fires, positions and fire hydrants and this app will just determine for e.g which fire should be displayed and returns the data.

see ./routes.

## Configuration
see ./middleware/config.js.