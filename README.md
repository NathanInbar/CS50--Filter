# CS50--Filter
Image Filters under pset4 of Harvard's CS50x Course

## Usage
```
$ filter [flag] infile outfile
```
## Examples

### Greyscale
```
$ filter -g images/tower.bmp grey.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](grey.bmp?raw=true "After")

### Horizontal Reflection
```
$ filter -r images/tower.bmp reflect.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](reflect.bmp?raw=true "After")

### Blur
```
$ filter -b images/tower.bmp blur.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](blur.bmp?raw=true "After")

### Edge Detection
```
$ filter -e images/tower.bmp edge.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](edge.bmp?raw=true "After")
