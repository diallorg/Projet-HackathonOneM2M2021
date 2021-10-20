from time import sleep
from SX127x.LoRa import *
from SX127x.board_config import BOARD
BOARD.setup()

#Les valeurs par défaut à moyenne portée après l'intialisation sont 434.0MHZ, Bw = 125 kHz, Cr = 4/5, Sf = 128 chips/symbol, CRC sur 13 dBm
lora.set_pa_config(pa_select=1)

    def _init_(self, verbose=False):

        super (LoRaRcvCont, self)._init_(verbose)
        self.set_mode(MODE.SLEEP)
        self.set_dio_mapping([0]*6)

    def start(self):
        self.reset_ptr_rx()
        self.set_mode(MODE.RXCONT)
        while True:
            sleep(.5)
            rssi_value = self.get_rssi_value()
            status = self.get_modem_status()
            sys.stdout.flush()

    def on_rx_done(self):
        print("\nReceived: ")
        self.clear_irq_flags(RXDone=1)
        payload = self.read_payload(nocheck=True)
        print(bytes(payload).decode("utf-8", 'ignore')
        self.set_mode(MODE.SLEEP)
        self.set_ptr_rx()
        self.set_mode(MODE.RXCONT)

            
    
