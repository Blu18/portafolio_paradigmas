+++
date = '2025-05-15'
draft = false
title = 'Practica 3: Paradigma Funcional'
+++

# Introducción
El paradigma funcional se basa en el uso de funcioneos matemáticas puras. Este estilo de progrmación en vez de centrars en cómo se ejecutan las tareas paso a paso o en la manipulación de objetos y sus estados, se enfoca en el "qué" se quiere lograr, tratando la computación como la evaluación de funciones.

En esta práctica se explicara un programa en Haskell sobre una lista de pendientes donde el usuario puede realizar acciones como agregar un pendiente, eliminar, mostrar la lista, etc.

# Desarollo 
El primer codigo a analizar es [Lib.hs](https://github.com/Blu18/portafolio_paradigmas/blob/master/todo/src/Lib.hs) donde se encuentra toda la logica del programa.

```haskell
module Lib
  ( prompt,
    editIndex,
  )
where
```
En este primer fragmento de declara el modulo libreria donde se exponen las funciones *prompt* y *editIndex* para que puedan ser utilizadas en otro archivo, en este caso sera utilizado en [Main.hs](https://github.com/Blu18/portafolio_paradigmas/blob/master/todo/app/Main.hs).

Depués se importan funciones de lista como  *isPrefixOf*, que se usa para verificar si una cadena comienza con otra.
```haskell
import Data.List
```

Ahora pasamos a la logica del codigo done primero tenemos la función putTodo.
```haskell
putTodo :: (Int, String) -> IO ()
putTodo (n, todo) = putStrLn (show n ++ ": " ++ todo)
```
El proposito de esta función es imprimir la tarea de la lista de pendientes junto a su indice por ejemplo: "0: Hacer tarea".

```haskell
prompt :: [String] -> IO ()
prompt todos = do
  putStrLn ""
  putStrLn "Test todo with Haskell. You can use +(create), -(delete), s(show), e(dit), l(ist), r(everse), c(lear), q(uit) commands."
  command <- getLine
  if "e" `isPrefixOf` command
    then do
      print "What is the new todo for that?"
      newTodo <- getLine
      editTodo command todos newTodo
    else interpret command todos
```
Esta función primero muestra lo que hacen los comando del programa y también se encarga de recibir el comando de entrada si el comando es *"e"* pasa a la funcion *editTodo*, y si es cualquier otro comando pasa a la función *interpret*.

```haskell
interpret :: String -> [String] -> IO ()
interpret ('+' : ' ' : todo) todos = prompt (todo : todos) -- append todo to the empty or previous todo list [] here.
interpret ('-' : ' ' : num) todos =
  case deleteOne (read num) todos of
    Nothing -> do
      putStrLn "No TODO entry matches the given number"
      prompt todos
    Just todos' -> prompt todos'
interpret ('s' : ' ' : num) todos =
  case showOne (read num) todos of
    Nothing -> do
      putStrLn "No TODO entry matches the given number"
      prompt todos
    Just todo -> do
      print $ num ++ ". " ++ todo
      prompt todos
interpret "l" todos = do
  let numberOfTodos = length todos
  putStrLn ""
  print $ show numberOfTodos ++ " in total"

  mapM_ putTodo (zip [0 ..] todos)
  prompt todos
interpret "r" todos = do
  let numberOfTodos = length todos
  putStrLn ""
  print $ show numberOfTodos ++ " in total"

  let reversedTodos = reverseTodos todos

  mapM_ putTodo (zip [0 ..] reversedTodos)
  prompt todos
interpret "c" todos = do
  print "Clear todo list."

  prompt []
interpret "q" todos = return ()
interpret command todos = do
  putStrLn ("Invalid command: `" ++ command ++ "`")
  prompt todos
```
En esta función es donde se interpretan los comandos del usuario y realiza una acción.
- __+__ : Cuando se ingresa este comando se agrega una nueva tarea a la lista, despues vuelve a llamar a la función *prompt*.
- __-__ : Elimina una tarea mediante su indice llamando a la función *deleteOne*, si el indice que proporciana el usario no es valido muestra un mensaje de error.
- __s__ : Muestra una taraa mediante su indice llamando a la función *showOne*, y muestra un mensaje si el indice es invalido.
- __l__ : Muestra todas las tareas junto con su indice y la cantidad de tareas que hay en la lista con la funcion *mapM_putTodo*.
- __r__ : Invierte el orden de las tareas y muestra la lista y el total con la función *reverseTodos*.
- __c__ : Elimina todas las tareas de la lista e imprime un mensaje, finalmente vuelve a llamar a la función *prompt*.
- __q__ : Termina el programa.

```haskell
deleteOne :: Int -> [a] -> Maybe [a]
deleteOne 0 (_ : as) = Just as
deleteOne n (a : as) = do
  as' <- deleteOne (n - 1) as
  return (a : as')
deleteOne _ [] = Nothing
```
Esta funcion es la que se manda a llamar con el comando *"-"*, esta funcion recibe un numero entero y una lista, si se recibe un 0 devuel la lista ignorando el primer elemento, si se recibe otro numero se aplica recursividad hasta llegar al indice correspondiente, y si el indice es un numero invalido regresa *Nothing*.

```haskell
showOne :: Int -> [a] -> Maybe a
showOne n todos =
  if (n < 0) || (n > length todos)
    then Nothing
    else Just (todos !! n)
```
Al igual que *deleteOne*, esta función rebice un entero y una lista, si el entero es menor a 0 y mayor a la longitud de la lista, es decir que es un indice invalido, regresa *Nothing*. 
Si el indice es valido regresa devuelve el elemento en la posición dada por el usuario con en operador !! que srive para accer al indice de una lista.

```haskell
editOne :: Int -> [a] -> String -> Maybe a
editOne n todos newTodo =
  if (n < 0) || (n > length todos)
    then Nothing
    else do
      Just (todos !! n)
```
Esta función es parecida a showOne, pero esta funcion se manda a llamar en editTodo para realizarle una modificación.

```haskell
editTodo :: String -> [String] -> String -> IO ()
editTodo ('e' : ' ' : num) todos newTodo =
  case editOne (read num) todos newTodo of
    Nothing -> do
      putStrLn "No TODO entry matches the given number"
      prompt todos
    Just todo -> do
      putStrLn ""

      print $ "Old todo is " ++ todo
      print $ "New todo is " ++ newTodo
      -- let index = head (map digitToInt num)
      -- let index = read num::Int
      -- print index

      let newTodos = editIndex (read num :: Int) newTodo todos -- Couldn't match expected type ‘Int’ with actual type ‘[Char]
      let numberOfTodos = length newTodos
      putStrLn ""
      print $ show numberOfTodos ++ " in total"
      mapM_ putTodo (zip [0 ..] newTodos)

      prompt newTodos
```
Esta función primero manda a llamar *editOne* si recibe *Nothing* como resultado muestra un mensaje de indice invalido, si el indice es valido muestra la tarea antigua utilizando ++ para concatenar cadenas y seguido de eso muestra un mensaje para la nueva tarea y lee la nueva tarea. Finalmente, actualiza el numero de tareas, muestra el numero de tareas y la lista completa.

```haskell
reverseTodos :: [a] -> [a]
reverseTodos xs = go xs []
  where
    go :: [a] -> [a] -> [a]
    go [] ys = ys
    go (x : xs) ys = go xs (x : ys) 

```
Esta funcion recibe dos listas como argumentos y utiliza la funcion *go* recursivamente para invertir la lista con cada recursion la funcion *go* añade el primer elemento de la lista original al principio de la nueva lista y lo elimina de la lista original.

Ahora anlizaremos el codigo de [Main.hs](https://github.com/Blu18/portafolio_paradigmas/blob/master/todo/app/Main.hs)
```haskell
import Configuration.Dotenv (defaultConfig, loadFile)
import Lib (prompt)
import System.Environment (lookupEnv)
import Web.Browser (openBrowser)
```
Empenzando tenemos la importación de modulos, donde podemos observar que se hace uso del codigo anteriormente explicado *Lib.hs* y además tenemos otros dos modulos que serviran para abrir una pagina web.

```haskell
main :: IO ()
main = do
  loadFile defaultConfig
  website <- lookupEnv "WEBSITE"

  case website of
    Nothing -> error "You should set WEBSITE at .env file."
    Just s -> do
      result <- openBrowser s
      if result
        then print ("Could open " ++ s)
        else print ("Couldn't open " ++ s)

      putStrLn "Commands:"
      putStrLn "+ <String> - Add a TODO entry"
      putStrLn "- <Int>    - Delete the numbered entry"
      putStrLn "s <Int>    - Show the numbered entry"
      putStrLn "e <Int>    - Edit the numbered entry"
      putStrLn "l          - List todo"
      putStrLn "r          - Reverse todo"
      putStrLn "c          - Clear todo"
      putStrLn "q          - Quit"
      prompt [] -- Start with the empty todo list.
```
En este codigo solo tenemos una función que se encarga de cargar el archivo de configuracion y de buscar el link de la pagina web dentro de un archivo *.env* que se deseea abrir, si encuentra el archivo y se abrio la pagina, mostrara un mensaje de exito de otro modo indicara que no se pudo abrir. Finalmente muestra el menu principal del programa donde se muestran los comandos mencionados de *Lib.h* y se llama la función *promr* con una lista vacía.

# Conclusión
En esta práctica se exploró el paradigma funcional con un programa en haskell para gestionar una lista de pendientes. Mediante el código analizado se pueden comprender conceptos claves del paradigma funcional, como la recursividad.