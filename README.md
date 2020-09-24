# CS50--Filter
Image Filters under pset4 of Harvard's CS50x Course

## Usage
```
$ filter [flag] infile outfile
```
## Examples

### Greyscale
```
$ filter -g tower.bmp grey.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](grey.bmp?raw=true "After")

### Horizontal Reflection
```
$ filter -r tower.bmp reflect.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](reflect.bmp?raw=true "After")

### Blur
```
$ filter -b tower.bmp blur.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](blur.bmp?raw=true "After")

### Edge Detection
```
$ filter -e tower.bmp edge.bmp
```
Before | After
----------------------------------------------|-------------------------------
![Before](images/tower.bmp?raw=true "Before") |![After](edge.bmp?raw=true "After")
