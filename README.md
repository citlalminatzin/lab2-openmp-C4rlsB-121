[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/-juK1o1b)
# scca-lab2-openmp

> **Objetivo.** Implementar programas en OpenMP que permitan solucionar problemas numéricos de manera eficiente.

# Entregables

Los entregables varían dependiendo del lenguaje que quieras utilizar. En cualquier caso tu código debe ser reproducible.

- Documentación
    - `README.md` con indicaciones de instalación (y dependencias si hay), compilación, y ejecución.
    - _Python_ 
        - Paquetes necesarios para reproducir el código (`requirements.txt`, `environment.yml` en caso de usar [conda](https://docs.conda.io/projects/conda/en/latest/user-guide/getting-started.html), `uv.lock` y `pyptoject.toml` en caso de usar [uv](https://docs.astral.sh/uv/getting-started/installation/)).
    - _C_
        - Indicar si se requiere alguna bandera especial de compilación.
- Código fuente
    - Escribir un archivo separado por cada problema a resolver.

# Instrucciones

Para cada ejercicio debes

- Analizar las variables y paralelizar el código usando directivas de OpenMP. Puedes entregarlo en Python (omp4py) o en C.
- Analizar el tiempo de ejecución en 2,4,6 y 8 hilos comparado con la ejecución secuencial del código.
- Calcula el speedup
- Grafica las curvas de aceleración obtenidas
- Reporta tus resultados en un .pdf (creado con LaTeX) o editando este `README.md`

# Problemas a resolver

1. **Hola mundo.** Escribe un programa que indique la cantidad de hilos usados en su ejecución y el rango de cada uno de los hilos.
2. **Producto de matrices.** Sean $A\in\textrm{Mat}(n,m)$, $B\in\textrm{Mat}(m,n)$ matrices, escribe un programa que realice el producto $AB$. Utiliza diferentes tipos de reparticion (STATIC, DYNAMIC, GUIDED) y la clausula `collapse`.
3. **Cálculo de pi.** Recordando que 

$$\int_0^1\frac{4}{1+x^2}=\pi$$

realiza el cálculo de la integral. Toma una partición con $N+1$ puntos, generando $N$ rectángulos de base $h=\frac{1}{N}$.

4. EXTRA: **Metodo de Jabobi.** Varios problemas (en general, de diversas ramas de las matemáticas) se pueden reducir a solucionar un sistema de ecuaciones lineales. Obtener una solucion por métodos tradicionales es extremadamente costoso en tiempo. Así, se vuelve necesario encontrar mètodos eficientes para hayar resultados numéricos. Paraleliza el código para uno de éstos métodos llamado método de Jacobi.

# Estructura de los commits

Recuerda que tus commits deben de iniciar con una palabra descriptiva de la siguiente lista:

- FEAT: Para indicar que se añade/quita una funcionalidad de tu código
- CHORE: Para acciones de limpieza que no afectan el funcionamiento del código
- REFACTOR: Reescritura del código que no afecta su funcionalidad
- FIX: Arregla un bug
- BUG: Se reporta un problema con la funcionalidad del código
- DOCS: Se añade o edita la documentación

De preferencia, haz que cada commit haga un solo cambio en un solo archivo. Siempre puedes regresar a un commit anterior.


# Referencias

Traducciones y código de _travaux practiques_ seleccionados de la versión 2.9 del curso de OpenMP del _Institut du Développement et des Ressources en Informatique Scientifique_.
