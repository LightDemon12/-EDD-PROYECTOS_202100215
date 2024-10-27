# Social Structure - Fase 1, Fase 2 & Fase 3

## Descripción del Proyecto

**Social Structure** es una aplicación que simula una red social utilizando estructuras de datos no lineales. Este proyecto tiene múltiples fases, con la **Fase 1** centrada en la implementación básica de las estructuras de datos y funcionalidades esenciales, la **Fase 2** enfocada en la adición de una interfaz gráfica de usuario (GUI), y la **Fase 3** destinada a mejorar la seguridad y la eficiencia de la aplicación.

---

## Objetivos de la Fase 1

### Objetivo General
- Aplicar los conocimientos del curso Estructuras de Datos en el desarrollo de una aplicación de red social.

### Objetivos Específicos
- Implementar estructuras de datos no lineales para gestionar usuarios, solicitudes de amistad, y publicaciones.
- Desarrollar una aplicación en consola utilizando el lenguaje de programación C++.
- Implementar funciones básicas para el registro de usuarios, manejo de solicitudes de amistad, y publicación de contenido.

---

## Objetivos de la Fase 2

### Objetivo General
- Ampliar las funcionalidades de la aplicación de consola mediante la implementación de una interfaz gráfica que permita una mejor interacción con los usuarios.

### Objetivos Específicos
- Implementar una GUI usando Qt para la interacción del usuario.
- Integrar las estructuras de datos ya implementadas con la interfaz gráfica.
- Mejorar el rendimiento del sistema mediante la optimización de las estructuras de datos y la adición de nuevas funcionalidades.

---

## Objetivos de la Fase 3

### Objetivo General
- Aplicar los conocimientos del curso Estructuras de Datos en el desarrollo de soluciones de software, enfocándose en la seguridad de la información del usuario.

### Objetivos Específicos
- Comprender y desarrollar distintos tipos de estructuras no lineales.
- Implementar una aplicación de escritorio utilizando el lenguaje de programación C++.
- Utilizar la herramienta Graphviz para graficar estructuras de datos no lineales.
- Incorporar conceptos de blockchain para la seguridad de los datos de los usuarios.
- Implementar algoritmos de grafos en la aplicación para optimizar el manejo de las relaciones de amistad.

---

## Funcionalidades Implementadas

### Fase 1

1. **Registro de Usuarios e Inicio de Sesión**
   - Registro de usuarios con información básica (nombres, apellidos, fecha de nacimiento, correo electrónico, contraseña).
   - Inicio de sesión con verificación de credenciales.
   - Eliminación de cuenta de usuario y actualización de estructuras relacionadas.

2. **Solicitudes de Amistad**
   - Envío de solicitudes de amistad.
   - Rechazo y aceptación de solicitudes de amistad.
   - Gestión de solicitudes mediante una pila para el receptor y una lista simple para el emisor.

3. **Matriz de Relaciones de Amistad**
   - Representación de relaciones de amistad utilizando una matriz dispersa.
   - Inserción de nuevas amistades en la matriz al aceptar solicitudes.

4. **Publicaciones**
   - Creación y almacenamiento de publicaciones en una lista doblemente enlazada.
   - Visualización del feed de publicaciones en una lista circular doblemente enlazada.

5. **Carga Masiva de Datos**
   - Carga de datos desde archivos JSON para usuarios, solicitudes y publicaciones mediante un usuario administrador.

### Fase 2

1. **Interfaz Gráfica (GUI)**
   - Se ha desarrollado una interfaz gráfica utilizando **Qt** que permite a los usuarios interactuar con el sistema de manera más intuitiva.
   - El sistema ahora cuenta con ventanas dedicadas para la administración, la gestión de publicaciones y la visualización de amigos.

2. **Gestión de Publicaciones**
   - Implementación de una ventana dedicada para la creación y visualización de publicaciones con imágenes.
   - Integración de un árbol binario para organizar las publicaciones por fecha.
   - Posibilidad de comentar publicaciones usando un **árbol B**.

3. **Optimización y Organización de Datos**
   - Las publicaciones ahora se organizan utilizando un **árbol binario completo**, lo que mejora la eficiencia en la búsqueda y ordenación de publicaciones.
   - El sistema ha sido optimizado para manejar grandes volúmenes de datos de forma eficiente, manteniendo la responsividad en la interfaz gráfica.

### Fase 3

1. **Cambio de Estructura de Relaciones de Amistad**
   - La matriz dispersa ha sido reemplazada por un **grafo no dirigido** utilizando una lista de adyacencia, para manejar las relaciones de amistad de forma más eficiente.
   - Cada vértice en el grafo representa un usuario, y las aristas representan las relaciones de amistad entre ellos.

2. **Sugerencias de Amistad**
   - Implementación de un sistema de sugerencia de amigos basado en la exploración de las distancias en el grafo.
   - Se recomienda a los usuarios que estén a una distancia de dos saltos (amigos de amigos) y se ponderan las sugerencias según la cantidad de amigos en común.

3. **Modificación de Perfil**
   - Los usuarios pueden ahora modificar sus datos personales como nombre, apellidos, fecha de nacimiento y contraseña desde la interfaz gráfica.

4. **Seguridad y Blockchain**
   - Incorporación de **conceptos de blockchain** para asegurar la integridad de los datos de los usuarios.
   - Cada acción importante (como cambios de perfil o publicaciones) se almacena en una cadena de bloques, asegurando que los datos sean inmutables y estén protegidos contra manipulaciones.

---

## Estructuras de Datos

- **Lista Simplemente Enlazada:** Maneja los usuarios registrados.
- **Pila:** Almacena las solicitudes de amistad recibidas.
- **Lista Doblemente Enlazada:** Almacena todas las publicaciones.
- **Lista Circular Doblemente Enlazada:** Muestra el feed de publicaciones de un usuario.
- **Grafo No Dirigido:** Reemplaza la matriz dispersa para representar las relaciones de amistad.
- **Árbol Binario Completo:** Utilizado para la organización de publicaciones por fecha.
- **Árbol B:** Implementado para almacenar y gestionar comentarios en publicaciones.

---

## Instrucciones de Uso

1. **Compilación y Ejecución:**
   - Asegúrate de tener un compilador de C++ y **Qt** instalado.
   - Compila el proyecto con un comando como `g++ -o social_structure main.cpp` (ajusta según tus archivos y compilador).
   - Ejecuta el programa con `./social_structure`.

2. **Registro de Usuario:**
   - Utiliza el menú de inicio o la interfaz gráfica para registrarte con los datos solicitados.

3. **Inicio de Sesión:**
   - Inicia sesión con el correo electrónico y contraseña registrados, tanto en consola como en la interfaz gráfica.

4. **Envío y Manejo de Solicitudes de Amistad:**
   - Envía, acepta o rechaza solicitudes de amistad desde el menú de usuario o la interfaz gráfica.

5. **Publicaciones:**
   - Crea y visualiza publicaciones a través del menú de publicaciones en consola o utilizando la GUI, con la opción de agregar imágenes.

6. **Modificación de Perfil:**
   - Modifica tu nombre, apellidos, fecha de nacimiento o contraseña desde el menú de configuración de la interfaz gráfica.

7. **Carga Masiva:**
   - Usa las opciones del administrador para cargar usuarios, solicitudes y publicaciones desde archivos JSON.

8. **Sugerencias de Amistad:**
   - Recibe recomendaciones de amigos basadas en el número de amigos en común y la distancia dentro del grafo de relaciones.

---

## Observaciones

- **Lenguaje de Programación:** C++
- **Herramienta para Gráficos:** Graphviz, Qt
- **Seguridad:** Blockchain
- **IDE:** Clion
- **Sistema Operativo:** Windows 10
