# flashback

Tool that supports manual application testing by fast GUI components comparison.

Flashback supports taking multiple screenshots, displaying and comparing them. Core component of application is **Screenshot Manager**.

## Screenshot Manager

Screenshot Manager is based on three elements:
1. **Screenshots** - most basic element
2. **Sets** of screenshots (TODO). First Screenshot in set is picturing the starting point state of tested component.
3. **Sessions** - contain multiple sets (TODO). Session can be saved to and loaded from hard drive (TODO).

### Screenshot

Screenshots can be taken outside Screenshot Manager through global hotkey.

####  Screenshot Overlay

All elements that can be displayed on screenshots:
1. Timestamp
2. Set index, color and label (TODO) at top position
3. Screenshot index and label (TODO)
4. Symbols of images (current session structure (TODO)

### Screenshots Set

Set of screenshots are created in Screenshot Manager. Screenshots can be freely moved inside set and between sets.

### Session

|Set|Set|...
---|:---:|:---:|:---
**Base image**|**x**|**x**|...
Comparable image|x|x|...
Comparable image|x|...|...
...|...|...|...

## Functions

| Functions | Shortcut |
|:-----------:|:----------:|
| Take Screenshot - global | PrintScr |
| Open/Close Screenshot Manager - global | Pause |
| Add Set | + |
| Delete Set | ? |
| Set base image| ? |
| Change Set | Left/Right |
| Change screenshot | Up/Down |
| Delete Screenshot | Delete |
| Save screenshot | ? |
| Save session | ? |
| Load screenshot | ? |
| Load session | ? |

## Supported platforms

1. Linux
2. Windows (TODO)
