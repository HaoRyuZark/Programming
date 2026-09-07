# Angular 

**Angular** is an opinionated, component based JavaScript/Typescript framework for GUIs. 

**Opinions**: 

- 

- 

- 

- 

--- 

## Installation & Set-Up

Run the following command to install the **cli-tool** which will provide both functionality and fast initialization for projects.

```bash 
sudo npm install -g @angular/cli
```

### Set-Up Project

```bash 
ng new <name_of_the_project>
```

After running it is going to ask you for the preferences of the project. By adding `--dry-run` we can 
simulate the creation.

--- 

## CLI Tool Commands 

- `ng serve`: runs the application in  developer mode.


--- 

## Project Structure


```txt 

```


--- 

## Angular Components

**Angular components** are UI-elements which consists of **logic** in a `.ts` file, **style** in a `.css` or `.scss` file and a definition in a `.html` file.
We can also use **inline** properties to declare everything in a single file.

To declare components we create both the files and also use the `@Component` decorator which has the following fields: 

- `selector`: name of the component, used when using the component inside another like: `<div><my-component/></div>`

- `standalone`:

- `imports`:

- `template`: 

- `style`: 

- `templateUrl`: 

- `sytleUrl`:


```ts 
@Component ({
    selector: 'app-root',
    standalone: true, 
    imports: [RouterOutlet],

})
export class AppComponent {

}
```

The class underneath is used to declare the custom functionality.

### Generating Components

```bash 
ng generate c header
```

#### Flags 

### Life-cycle

###


--- 

## Angular Data-Binding

### Signals 

### Variables


--- 

## Passing Data

--- 

## Event Listeners

--- 

## Routers 

--- 

## Services 

**Services** are reusable pieces of code which can be injected.

--- 

## HTTP Requests 


--- 

## Directives 

### ngIf 

### ngFor

### 

### 


--- 

## Dynamic Templates

--- 

## Pipes 

--- 

## Forms


--- 






