<template>
  <div>
    <div id="circles">
      <label for="">Show areas at risk</label>
      <input type="checkbox" @change="showPrevent()" checked>
      <label for="">Show itinerary</label>
      <input type="checkbox" @change="showRoutes()" checked>
      <label for="">Show water sources</label>
      <input type="checkbox" @change="showHydrants()" checked>
      <p>
        <strong id="purple">✺</strong> is a fire,
        <strong id="red">✺</strong> is a high risk area,
        <strong id="orange">✺</strong> is a risk area.
      </p>
    </div>
    <l-map style="height: 91.8vh" :zoom="zoom" :center="center">
      <l-tile-layer :url="url" :attribution="attribution"></l-tile-layer>
      <div id="fire" v-for="circle in fireCircles" :key="circle.id">
        <l-circle :lat-lng="circle.center" :radius=5 :color=purple></l-circle>
      </div>
      <div id="prevent" v-for="circle in preventCircles" :key="circle.id">
        <l-circle :lat-lng="circle.center" :radius=circle.radius :color=circle.color></l-circle>
      </div>
      <div id="hydrant" v-for="circle in hydrantCircles" :key="circle.id">
        <l-circle :lat-lng="circle.center" :radius=10 :color=circle.color></l-circle>
      </div>
      <div v-for="waypoint in waypoints" :key="waypoint[0].lat">
        <l-routing-machine :waypoints="[{lat:waypoint[0].lat, lng:waypoint[0].lng}, { lat: waypoint[1].lat, lng: waypoint[1].lng }]"/>
      </div>
    </l-map>
  </div>
</template>

<style>
  @import url('https://fonts.googleapis.com/css2?family=Noto+Sans+Mono:wght@300&display=swap');
  
  html{
    font-family: 'Noto Sans Mono', monospace;
    font-size: 0.8em;
  }

  #purple{
    color: purple;
  }

  #red{
    color: red;
  }

  #orange{
    color: orange;
  }
</style>

<script>

import {LMap, LTileLayer, LCircle} from 'vue2-leaflet';
import LRoutingMachine from '@/components/LRoutingMachine'
import "leaflet/dist/leaflet.css";
import { Icon } from 'leaflet';
import axios from 'axios';

delete Icon.Default.prototype._getIconUrl;

Icon.Default.mergeOptions({
  iconRetinaUrl: require('leaflet/dist/images/marker-icon-2x.png'),
  iconUrl: require('leaflet/dist/images/marker-icon.png'),
  shadowUrl: require('leaflet/dist/images/marker-shadow.png'),
});

export default {
  components: {
    LMap,
    LTileLayer,
    LCircle,
    LRoutingMachine
  },
  data () {
    return {
      // fire-map server ip
      ip: "http://localhost:4000",

      url: 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
      attribution:
        '&copy; <a target="_blank" href="http://osm.org/copyright">OpenStreetMap</a> contributors',
      zoom: 20,
      center: [43.61659243175874, 7.071922849252316],
      purple: 'purple',
      fireCircles:[],
      preventCircles: [],
      preventCirclesCache: [],
      preventPause: 0,
      hydrantCircles: [],
      hydrantCirclesCache: [],
      hydrantPause: 0,
      waypoints: [],
      waypointsCache: [],
      waypointPause: 0
    };
  },
  mounted(){
    this.getServerFireValues();
    this.getServerPreventValues();
    this.getServerHydrantValues();
  },
  methods:{
    getServerFireValues(){
     axios.get(this.ip + "/fires")
      .then(response => {
        this.fireCircles = [];
        this.waypoints = [];
        response.data.forEach(data => {
          this.fireCircles.push(data);

          let route = [
            { lat: 43.628863292640425, lng: 7.044738173675914 },
            { lat: data.center[0], lng: data.center[1] }
          ];
          this.waypointsCache.push(route);
          if(this.waypointPause == 0)
            this.waypoints.push(route);
        });
      })
      .catch(e => {
        this.errors.push(e);
      });

      setTimeout(this.getServerFireValues, 10000);
    },

    getServerPreventValues(){
     axios.get(this.ip + "/prevents")
      .then(response => {
        this.preventCircles = [];
        this.preventCirclesCache = [];
        response.data.forEach(data => {
          this.preventCirclesCache.push(data);
          if(this.preventPause == 0)
            this.preventCircles.push(data);
        });
      })
      .catch(e => {
        this.errors.push(e);
      });

      setTimeout(this.getServerPreventValues, 10000);
    },

    getServerHydrantValues(){
     axios.get(this.ip + "/hydrants")
      .then(response => {
        this.hydrantCircles = [];
        response.data.forEach(data => {
          let circle = {
            id: data.id,
            center: data.center,
            color: 'blue'
          }
          this.hydrantCirclesCache.push(circle);
          if(this.hydrantPause == 0)
            this.hydrantCircles.push(circle);
        });
      })
      .catch(e => {
        this.errors.push(e);
      });
    },

    showPrevent(){
      if(this.preventPause == 1){
        this.preventCircles = this.preventCirclesCache;
        this.preventPause = 0;
      }
      else{
        this.preventCircles = [];
        this.preventPause = 1;
      }
    },

    showRoutes(){
      if(this.waypointPause == 1){
        this.waypoints = this.waypointsCache
        this.waypointPause = 0;
      }
      else{
        this.waypoints = [];
        this.waypointPause = 1;
      }
    },

    showHydrants(){
      if(this.hydrantPause == 1){
        this.hydrantCircles = this.hydrantCirclesCache
        this.hydrantPause = 0;
      }
      else{
        this.hydrantCircles = [];
        this.hydrantPause = 1;
      }
    }
  }
}
</script>
