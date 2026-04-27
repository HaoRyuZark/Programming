# XML

**XML**, **extensible markup language** is a markup language used for configurations for the structured exchange of data.

The name comes from the fact that tags are not pre-defined, but instead their are defined by the users.

## XML Prolog

This is a header provided at the start of the file which defined the version and the used encoding for the characters.

```xml
<?xml version="1.0" encoding="UTF-8">
```

---

## Tag Definition

All tags must be closed. Also, for the definition of the **attributes** inside the tag definition must be quoted.

```xml
<my_custom_tag attr="some attribute">
    <name>Migumin</name>
</my_custom_tag>
```

---

## XML Namespaces

The namespace can be defined by an `xmlns` attribute at the start taf of an element, then all children with the same prefix are associated with the same
namespace.

It is a good practice to declare this namespaces at the start of the file inside the root element. So that there is not need in defining them again.

```xml
<root xmlns:d="https://domain.com" xmlns:f="https://fumino.jp">

<d:domi>
    <d:ele>Hoho</d:ele>
</d:domi>

<f:fumi>
    <f:slogan>Best Waifu</f:slogan>
</f:fumi>
</root>
```

If we instead use only use `xmlns="something"`, then the elements created inside the tag do not need to prefixed with the chosen prefix.

---

## DOM

The **DOM** or **Document Object Model** is a structure which represents the content of xml or html file as tree structure consisting of the tags its contents and children.

---

## XML Validation

This is done by checking that the tags are properly closed, the obligatory tags are not empty, etc.

--- 

## XML Schema

Schemas are a way of defining the structure and order of an xml file. Most of the times not important, but quite 
interesting to be able to defined the the necessary fields in such a precisse way.

--- 

## XML Attributes

Attributes are used for meta data, and can technically be equivalent to single non nested values of an object. 
In contrast to elements they are only single valued and as strings do not allow nesting.

```xml
<woman name="Maria">
    <husband profession="Programmer"> 
        <man name="Pedro">  
        </man> 
    </husband>
</woman>
```

--- 

## Miscellaneous

XML comes with beig suite of tools and other utilities for querying documents, validate schemas, create hyperlinks, styling and a lot 
more. Learning them depends on the context and use case. It is imporant to notice that other formats such as JSON, YAML and TOML 
are nowadays more used to its simplicity.

