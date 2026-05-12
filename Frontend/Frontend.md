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

It is important to note some key elements: 

- When parsing the html, both css and javascript are blocking operations. This means that when a css or javascript tags are parsed the 
client sends additional requests to get the files.

- When javascript is returned from the server the script is executed right after, which means that the rendering of the page is stopped.
To avoid the `async` or `defer` keywords. `defer` is preferred for when the script should execute after the rendering, while `async` gets executed as soon 
as the script has been completely send to the client.

- The object resonsible for the styling after the parsing of the css file is called the CSSOM

--- 

## Template Engines

A **template engine** is a piece of software which takes html and expands it with extra logic with allows for programatically 
definition of components which are to be processed by the engine to then plain html.

--- 

## Multi Page Application

The different pages of an application are sended in different responses from the server. 
The rendering is done server sided, which leads to multiple request to the server.

--- 

## Single Page Application

In this architecture the server sends one html with all of the css and js files necessary to the client. The only time 
a new request to the server is made, is when new data or some intense computation is needed.

--- 

## Rendering Patterns

**Rendering** is the process of processing data with code to then be displayed on the site.

- **Static**: This is the classical way of defining websites as static html and css files. The approach is well suited for sites where there is almost 
no change.

- **Multi Page**: The appereance of the page is determined by the data fetched from the database. A drawback is that for each tab or view of the page a whole 
re-load is necessary.

- **Single Page**: The client receives a shell of the page which includes the visuals, but for updating the displayed data separate requests are needed.

- **Server Side Rendering**: The client makes a request to the server which renders the full page with html, css and data; then it is sendend to client, where then JS 
handles the other future request to the server for updating the content like in a single page application.

- **Staitc Site Generation**: HTML is redered in advance in the server and then it gets hydrated after the first pageload.

- **Incremental Static Regeneration**: Simila to SSG, but only new pages are re-loaded when a cache miss happens.

- **Partial Hydration**: Proccess of rendering only partial parts of the page.

- **Island Architecture**: Even finner partial hydration only for special components which need javascript.

--- 

## Lazy Loading

**Lazy loading** is the concept of loading data only when it is requiered. In frontend development it can be applied to performing
certain requests for showing certain elements only when the user requests to do so. An advantage is that the number of requests to the server
is reduced which also reduces the amount of rendenring leading to an improvement for the performance.

  

---

# HTML 

--- 

# CSS 

--- 

# PHP
