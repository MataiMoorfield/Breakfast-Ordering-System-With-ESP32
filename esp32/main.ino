#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    // HTML 
    String htmlContent = "<html><head><style>";
    htmlContent += "body {font-family: Arial, sans-serif; margin: 20px;}";
    htmlContent += "form {max-width: 400px; margin: auto;}";
    htmlContent += "label {display: block; margin: 10px 0;}";
    htmlContent += "select, input, textarea {width: 100%; padding: 8px; margin: 8px 0;}";
    htmlContent += "input[type='submit'] {background-color: #4CAF50; color: white;}";
    htmlContent += "textarea {width: 100%; padding: 8px; margin: 8px 0; resize: vertical;}";
    htmlContent += "</style></head><body>";
    htmlContent += "<h2>Welcome to the Breakfast Cafe!</h2>";
    htmlContent += "<form action='/submit' method='POST' id='orderForm'>";
    htmlContent += "<label for='name'>Name:</label><input type='text' name='name' required>";
    htmlContent += "<label for='breakfast_type'>Breakfast Item:</label><select name='breakfast_type' id='breakfast_type' onchange='updateToppings()' required>";
    htmlContent += "<option value='' disabled selected>Please select</option>";
    htmlContent += "<option value='Pancakes'>Pancakes</option>";
    htmlContent += "<option value='Waffles'>Waffles</option>";
    htmlContent += "<option value='French Toast'>French Toast</option>";
    htmlContent += "<option value='Omelette'>Omelette</option>";
    htmlContent += "<option value='Scrambled Eggs'>Scrambled Eggs</option>";
    htmlContent += "<option value='Bagel with Cream Cheese'>Bagel with Cream Cheese</option>";
    htmlContent += "<option value='Breakfast Burrito'>Breakfast Burrito</option>";
    htmlContent += "<option value='Fruit Bowl'>Fruit Bowl</option>";
    htmlContent += "<option value='Yogurt Parfait'>Yogurt Parfait</option>";
    htmlContent += "</select>";
    htmlContent += "<label for='toppings'>Toppings:</label><select name='toppings' id='toppings' required>";
    htmlContent += "<option value='' disabled selected>Please select</option>";
    htmlContent += "</select>";
    htmlContent += "<label for='size'>Size:</label><select name='size' required><option value='S'>Small</option><option value='M' selected>Medium</option><option value='L'>Large</option></select>";
    htmlContent += "<label for='extras'>Extras:</label><textarea name='extras' rows='4'></textarea>";
    htmlContent += "<label for='notes'>Notes:</label><textarea name='notes' rows='4'></textarea>";
    htmlContent += "<input type='submit' value='Place Order'></form>";
    htmlContent += "</body><script>";
    htmlContent += "function updateToppings() {";
    htmlContent += "    var breakfastType = document.getElementById('breakfast_type').value;";
    htmlContent += "    var toppingsSelect = document.getElementById('toppings');";
    htmlContent += "    toppingsSelect.innerHTML = '';"; // Clear previous options
    htmlContent += "    if (breakfastType === 'Pancakes') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Syrup\">Syrup</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Butter\">Butter</option>';";
    htmlContent += "    } else if (breakfastType === 'Waffles') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Syrup\">Syrup</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Whipped Cream\">Whipped Cream</option>';";
    htmlContent += "    } else if (breakfastType === 'French Toast') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Syrup\">Syrup</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Powdered Sugar\">Powdered Sugar</option>';";
    htmlContent += "    } else if (breakfastType === 'Omelette') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Cheese\">Cheese</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Ham\">Ham</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Tomatoes\">Tomatoes</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Mushrooms\">Mushrooms</option>';";
    htmlContent += "    } else if (breakfastType === 'Scrambled Eggs') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Cheese\">Cheese</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Spinach\">Spinach</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Bacon\">Bacon</option>';";
    htmlContent += "    } else if (breakfastType === 'Bagel with Cream Cheese') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Cream Cheese\">Cream Cheese</option>';";
    htmlContent += "    } else if (breakfastType === 'Breakfast Burrito') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Salsa\">Salsa</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Guacamole\">Guacamole</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Sour Cream\">Sour Cream</option>';";
    htmlContent += "    } else if (breakfastType === 'Fruit Bowl') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Banana\">Banana</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Strawberries\">Strawberries</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Blueberries\">Blueberries</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Granola\">Granola</option>';";
    htmlContent += "    } else if (breakfastType === 'Yogurt Parfait') {";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Granola\">Granola</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Strawberries\">Strawberries</option>';";
    htmlContent += "        toppingsSelect.innerHTML += '<option value=\"Blueberries\">Blueberries</option>';";
    htmlContent += "    }";
    htmlContent += "}";
    htmlContent += "</script></html>";

    request->send(200, "text/html", htmlContent);
  });

  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest* request) {
    String name = request->arg("name");
    String breakfastType = request->arg("breakfast_type");
    String toppings = request->arg("toppings");
    String size = request->arg("size");
    String extras = request->arg("extras");
    String notes = request->arg("notes");

    // Check for required fields and valid breakfast type
    if (name.isEmpty() || size.isEmpty() || breakfastType.isEmpty() || breakfastType == "Please select") {
      // Display an error message if any required field is empty or breakfast type is not selected
      String errorMessage = "<html><body><h2>Error: Please fill in all required fields and select a valid breakfast item.</h2></body></html>";
      request->send(400, "text/html", errorMessage);
    } else {
      // HTML content for the order submission page with consistent styling
      String submitPageContent = "<html><head><style>";
      submitPageContent += "body {font-family: Arial, sans-serif; margin: 20px;}";
      submitPageContent += "h2 {color: #4CAF50;}";
      submitPageContent += "p {margin-top: 10px;}";
      submitPageContent += "</style></head><body>";
      submitPageContent += "<h2>Order Received! It will be delivered to " + name + "</h2>";
      submitPageContent += "<p><strong>Name:</strong> " + name + "</p>";
      submitPageContent += "<p><strong>Breakfast Item:</strong> " + breakfastType + "</p>";
      submitPageContent += "<p><strong>Toppings:</strong> " + toppings + "</p>";
      submitPageContent += "<p><strong>Size:</strong> " + size + "</p>";
      submitPageContent += "<p><strong>Extras:</strong> " + extras + "</p>";
      submitPageContent += "<p><strong>Notes:</strong> " + notes + "</p>";
      submitPageContent += "</body></html>";

      // Send data via Serial to the computer
      Serial.print("Breakfast Order - Name: ");
      Serial.print(name);
      Serial.print(", Breakfast Item: ");
      Serial.print(breakfastType);
      Serial.print(", Toppings: ");
      Serial.print(toppings);
      Serial.print(", Size: ");
      Serial.print(size);
      Serial.print(", Extras: ");
      Serial.print(extras);
      Serial.print(", Notes: ");
      Serial.println(notes);

      request->send(200, "text/html", submitPageContent);
    }
  });

  server.begin();
}

void loop() {
  // Your other code here
}
