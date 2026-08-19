# XML

**XML**, **extensible markup language** is a markup language used for configurations for the structured exchange of data.

The name comes from the fact that tags are not pre-defined, but instead their are defined by the users.

## XML Pro-log

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

The **namespace** can be defined by an `xmlns` attribute at the start tag of an element, then all children with the same prefix are associated with the same
namespace.

It is a good practice to declare this namespaces at the start of the file inside the root element. So that there is not need in defining them again.

```xml
<root xmlns:d="https://domain.com" xmlns:f="https://fumino.com">

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

**Schemas** are a way of defining the structure and order of an xml file. Most of the times not important, but quite 
interesting to be able to defined the necessary fields in such a precise way.

We can define a schema using the **XSD** or **XML Schema Definition**. This is a language which allows to define the structure of an xml file.

```xml
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
  <xs:element name="person">
    <xs:complexType>
      <xs:sequence>
       <xs:element name="name" type="xs:string"/>
       <xs:element name="age" type="xs:integer"/>
        </xs:sequence>
    </xs:complexType>
  </xs:element>
</xs:schema>
```

### Schema Tags

- `xs:element`: Defines a new element with a name and type.

- `xs:complexType`: Defines a complex type which can contain other elements.
- `xs:sequence`: Defines a sequence of elements which must appear in the order defined.
- `xs:choice`: Defines a choice of elements which can appear in any order.
- `xs:attribute`: Defines an attribute for an element.
- `xs:restriction`: Defines a restriction on an element or attribute.
- `xs:extension`: Defines an extension of an element or attribute.
- `xs:annotation`: Defines an annotation for an element or attribute.
- `xs:documentation`: Defines documentation for an element or attribute.
- `xs:import`: Defines an import of another schema.
- `xs:include`: Defines an inclusion of another schema.
- `xs:redefine`: Defines a redefinition of another schema.
- `xs:group`: Defines a group of elements which can be reused in other schemas.
- `xs:attributeGroup`: Defines a group of attributes which can be reused in other schemas.
- `xs:any`: Defines an element which can contain any other element.

### Schema Types

- `xs:string`: Defines a string type.
- `xs:integer`: Defines an integer type.
- `xs:decimal`: Defines a decimal type.
- `xs:boolean`: Defines a boolean type.
- `xs:date`: Defines a date type.
- `xs:time`: Defines a time type.
- `xs:dateTime`: Defines a dateTime type.
- `xs:duration`: Defines a duration type.
- `xs:base64Binary`: Defines a base64Binary type. 

### Schema Attributes

- `name`: Defines the name of an element or attribute.
- `type`: Defines the type of an element or attribute.
- `minOccurs`: Defines the minimum number of occurrences of an element.
- `maxOccurs`: Defines the maximum number of occurrences of an element.
- `use`: Defines whether an attribute is required or optional.  
- `default`: Defines the default value of an attribute.
- `fixed`: Defines a fixed value of an attribute.
- `ref`: Defines a reference to a named element or attribute.

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

