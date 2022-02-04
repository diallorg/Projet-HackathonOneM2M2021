# HEPHAESTUS PROJECT / Fire-server

## Description 
This is a REST API that creates the relation between the middlenodes, the database and the fire-map.
It can also launch a Python script that sends an SMS.

## About this app
Backend server developed in NodeJS with ExpressJS, the app establishes the relation between the front-end VueJS client server and the Infrastructure Node.
It also permits to send a text message if a fire is detected.

## Prerequisites
Download nodeJS and npm.
Deploy a mongoDB database wherever you want.

## Start 
Infrastructure Node and MiddleNodes has to be started, Application Entities and containers created.
Clone this repo, go inside the folder,
set the configuration, see "middleware/config.js",
run :
```sh
npm i && npm run start
```
## What it does when starting
If the infrastructure node is not set, just don't call those functions
### Discover
At launch, the app will look for all the Middle Nodes present in the Infrastructure Node, and will store in a database :
  - The Middle Node,
  - His Application Entites,
  - His Containers.

See "./middleware/discover.js".

### Subscribe
At launch, the app will subscribe to every container discovered previously according to all the sensors specified in "middleware/config.js".

see "./middleware/subscribe.js".

Each sensor will be specified to post on each file they are supposed to in "./routes/inReceivers/".

### Listen
After having subscribed, the app will listen for each subscription sector as, humidity, temperature, wind and flame.
See "./routes/inReceivers".
After receiving a request, the app will store in the database the new event, depending on what kind of data is transmitted, there can be additional events (e.g send sms alert for fire).

In the other hand, the app keeps a relation between the database and the Vue.JS client.
The client will ask for fires, positions and fire hydrants and this app will just determine for e.g which fire should be displayed and returns the data.

see "./routes".

### Listen
If a fire is POST to "./send/flame" the app will launch a python scrip that sends an SMS.
## Configuration
see "./middleware/config.js".