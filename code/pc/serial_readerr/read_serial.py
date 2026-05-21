import serial
import json
import csv
from datetime import datetime

PORT = " COM3"
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=1)

# will output csv file

timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
csv_file = f"angle_log_{timestamp}.csv"

with open(csv_file, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["t_ms", "angle_deg"])

    print("Listening for packets...")

    while True:
        try:
            line = ser.readline().decode("utf-8").strip()

            if not line:
                continue

            # json packets  processing
            if line.startswith("{")and line.endswith("}"):
                data = json.loads(line)
                t = data["t"]
                angle = data["angle"]

                writer.writerow([t,angle])
                print(f"t={t}, angle={angle}")

        except KeyboardInterrupt:
            print("Stopped.")
            break
        except Exception as e:
            print("Error: ", e)


