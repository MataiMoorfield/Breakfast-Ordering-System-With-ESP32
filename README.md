# Breakfast-Ordering-System-with-ESP32
A simple web based breakfast ordering system with the ESP32 for cafés. Full video [here]()

> [!NOTE]
> This is a system I'm currently developing for cafés to handle orders, both food and drinks.

> [!IMPORTANT]
> This is a in-porgress porject. It's not fully completed and will be updated.

## How to run

Clone the folder:
```
git clone https://github.com/MataiMoorfield/Breakfast-Ordering-System-With-ESP32.git
```
Install the necessary libraries:
```
pip install -r requirements.txt
```
Update the WiFi information for your network in the `main.ino` code and install the liabries to Arduino IDE. Upload the code to the ESP32. View the serial monitor to make sure it's connected to WiFi and view the local IP of the ESP32.

> [!TIP]
> Don't run the Python script with tthe Arduino IDE open

Run the `main.py` script while the ESP32 is plugged in.
```
cd python
python main.py
```

Enter the IP of the ESP32 in a web browser. A simple ordering form opens. When the form is completed and submitted, the order will appear on the Python GUI. When selected, the order can be completed and disappears.

<img width="717" alt="Screenshot 2024-02-17 at 9 19 36 AM" src="https://github.com/MataiMoorfield/Breakfast-Ordering-System-With-ESP32/assets/138086469/9f459a7f-11fb-42c2-8220-c585c966f0be">

Above: The web breakfast ordering system

Below: The Pyhton GUI

<img width="1013" alt="Screenshot 2024-02-17 at 9 20 31 AM" src="https://github.com/MataiMoorfield/Breakfast-Ordering-System-With-ESP32/assets/138086469/7322bce2-c1b1-472e-a419-f02c138bb975">

