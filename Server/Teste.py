import pandas as pd

DEBITADO = 1
SALDOINSUFICIENTE = 0
RFIDINVALIDO = -1

def verificaSaldo(valor, rfid):
  data = pd.read_csv("saldos.csv")
  for i in range(data["RFID"].size):
    if(data["RFID"][i] == rfid):
      if(data["Saldo"][i] > valor):
        data["Saldo"][i] -= valor
        data.to_csv("saldos.csv", index=0)
        return DEBITADO
      else:
        return SALDOINSUFICIENTE
  return RFIDINVALIDO

print(verificaSaldo(1, 1))