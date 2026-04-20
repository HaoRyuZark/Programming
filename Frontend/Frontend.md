# Frontend 

The **frontend** of an application cosists on the protocols, logic and 
functinalities provided for a client in server client communication.

It mostly consists on display logic for the GUI and small data processing with data 
fetched from the server.

--- 

## Displaying Proccess 

1. **Request**: A request is made and the server returns the `html`. 
2. **DOM**: The document object model is created in memory. 
3. **Render Tree**: This structure is used to determine which elements need to be redered.
4. **Styling**: The styles specified in the `css` file are applyed to the html elements in the render tree.
5. **Hydration**: The javascript functinalities are injected into the redered components.

--- 

## Multi Page Application

The different pages of an application are sended in different responses from the server. 
The rendering is done server sided, which leads to multiple request to the server.

--- 

## Single Page Application

In this architecture the server sends one html with all of the css and js files necessary to the client. The only time 
a new request to the server is made, is when new data or some intense computation is needed.

--- 

# HTML 

--- 

# CSS 

--- 

# PHP
