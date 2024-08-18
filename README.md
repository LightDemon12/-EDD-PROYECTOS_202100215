# Social Structure - Fase 1

## Descripción del Proyecto

**Social Structure** es una aplicación de consola que simula una red social utilizando estructuras de datos no lineales. Este proyecto se desarrollará en tres fases, con la Fase 1 centrada en la implementación básica de las estructuras de datos y funcionalidades esenciales.

## Objetivos de la Fase 1

### Objetivo General
- Aplicar los conocimientos del curso Estructuras de Datos en el desarrollo de una aplicación de red social en consola.

### Objetivos Específicos
- Implementar estructuras de datos no lineales para gestionar usuarios, solicitudes de amistad, y publicaciones.
- Desarrollar una aplicación en consola utilizando el lenguaje de programación C++.
- Implementar funciones básicas para el registro de usuarios, manejo de solicitudes de amistad, y publicación de contenido.

## Funcionalidades Implementadas

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

## Estructuras de Datos

- **Lista Simplemente Enlazada:** Maneja los usuarios registrados.
- **Pila:** Almacena las solicitudes de amistad recibidas.
- **Lista Doblemente Enlazada:** Almacena todas las publicaciones.
- **Lista Circular Doblemente Enlazada:** Muestra el feed de publicaciones de un usuario.
- **Matriz Dispersa:** Representa las relaciones de amistad entre usuarios.

## Instrucciones de Uso

1. **Compilación y Ejecución:**
   - Asegúrate de tener un compilador de C++ instalado.
   - Compila el proyecto con un comando como `g++ -o social_structure main.cpp` (ajusta según tus archivos y compilador).
   - Ejecuta el programa con `./social_structure`.

2. **Registro de Usuario:**
   - Utiliza el menú de inicio para registrarte con los datos solicitados.

3. **Inicio de Sesión:**
   - Inicia sesión con el correo electrónico y contraseña registrados.

4. **Envío y Manejo de Solicitudes de Amistad:**
   - Envía, acepta o rechaza solicitudes de amistad desde el menú de usuario.

5. **Publicaciones:**
   - Crea y visualiza publicaciones a través del menú de publicaciones.

6. **Carga Masiva:**
   - Usa las opciones del administrador para cargar usuarios, solicitudes y publicaciones desde archivos JSON.

## Observaciones

- **Lenguaje de Programación:** C++
- **Herramienta para Gráficos:** Graphviz
- **IDE:** Libre
- **Sistema Operativo:** Libre


