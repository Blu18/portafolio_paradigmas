+++
date = '2025-02-21T10:20:03-08:00'
draft = false
title = 'Practica 0: Markdown, Git & Hugo'
+++

# Introducción
Esta practica se divide en tres partes las cuales son sintaxis y uso de Markdown, uso de Git y Github y por ultimo se combinan los conocimientos adquiridos de Markdown y Git para generar páginas estaticas con Hugo y Github Pages.

# Desarrollo
### Sintaxis y uso de Markdown:
Para esta primera parte se vio en el laboratorio las bases de markdown a continuacion se muestra lo visto en clase:

#### Encabezados:
###### En markdown se puede utilizar el simbolo # para crear encabezados
<!--Esto es un comentario-->

# Encabezado 1

## Encabezado 2

### Encabezado 3

#### Encabezado 4

##### Encabezado 5

#### Tipos de letra
##### Se pueden utilizar diferentes tipo de letra aqui se muestran los más basicos. ** o _ _ para italica, ** ** 0 __ __ para negritas y ~~~~para texto tachado

<!--Itálicas-->
Este es un texto en *itálica*

Este es un texto en _itálica_

<!--Negritas-->
Este es un texto en **negritas**

Este `es un texto` en __negritas__

<!--Tachado-->
Este es un texto ~~tachado~~

#### Listas
##### Para realizar listas se utiliza * o 1., 2., n., para realizar listas enumeradas

<!--UL-->
* Elemento 1
* Elemento 2
* Elemento 3
  * Elemento 3.1
  * Elemento 3.2
    * Elemento 3.2.1
* Elemento 4

<!--OL-->
1. Elemento 1
1. Elemento 2
1. Elemento 3
    1. Elemento 3.1
    1. Elemento 3.2
1. Elemento 4

#### Enlaces
##### Markdown permite insertar enlaces de paginas web asignandoles un alias y una descripcion de la siguiente manera \[Alias\]\(Link "Descripción"\)
<!--Enlaces-->
[Google](http://www.google.com "Buscador google")

[UABC](http://www.uabc.mx "Sitio Universitario")

#### Imagenes
##### Markdown también permite insertar imagenes ya sea cargadas desde el dispositivo o de internet.
<!--Imagenes-->
Imagen cargada desde internet:

[![Imagen de internet](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSb7LQOtYRjJh_0v_rfXK8iNxH1ICUA_Gp8BA&s)](http://www.google.com)

Imange cargada desde dispositivo:

[![Imagen de dispositivo](./images/google.jpg)](http://www.google.com)


#### Bloques de código
##### Markdown soporta una gran variedad de lenguajes de programación a continuacion se muestran algunos cuantos:
<!--Bloques de código-->
```txt
This is a code block
This is the second line of the code block
```

```python
print("Hola mundo!")
```

```javascript
console.log('Hello world!')

const test = ()
```

```html
<h1>Hola mundo!</h1>
```
#### Tablas
<!--Tablas-->
| Productos | Precio | Cantidad |
| --------- | ------ | -------- |
| Laptop    | 3.3    | 2        |
| Mouse     | 13.3   | 1        |

#### Notas
<!--Notas-->
>Esto es una nota

#### Lista de tareas
<!--Tareas-->
* [x] Primera tarea
* [ ] Segunda tarea
* [x] Tercera tarea
* [ ] Cuarta tarea

#### Divisores horizontales
<!--Divisores horizontales-->
***

---

___

#### Menciones
<!--Menciones-->
@darthrookie :+1: :smile:

### Uso de Git y GitHub:
En la segunda parte de esta practica se vieron las bases de *Git* y *GitHub* y se utilizaron los siguientes comandos:

* git init - Crear repositorio vacio.
* git status - Ver el estado del directorio en el que se esta trabajando.
* git add - Añade archivos al staging area para alistarlos antes de hacer commit.
* git commit - Guarda el contenido del staging area en el repositorio local.
* git push - Sube los comnnit del repositorio local al repositorio de Github.

En esta practica se creo un repositorio espcialmente para esta materia donde se encontraran todos los reportes de practica y codigos utilizados en clase

[![Repositorio](./images/github.png)](https://github.com/Blu18/portafolio_paradigmas.git)

### Pagina estatica: