<script>
import { Line } from 'vue-chartjs'

export default {
  extends: Line,
  props: {
    data: {
      type: Array,
      required: true
    }
  },
  mounted () {
    // Overwriting base render method with actual data.
    this.renderChart(this.data);
    console.log("Rendering")
  }
}
</script>