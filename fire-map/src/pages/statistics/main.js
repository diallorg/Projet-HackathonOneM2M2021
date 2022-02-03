import Vue from 'vue'
import App from './App.vue'

new Vue({
  data(){
    return{
      test: "oui"
    }
  },
  render: h => h(App)
}).$mount('#app')