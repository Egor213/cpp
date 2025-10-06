Контекст содержит различную информацию

+ `context.WithCancel(parent)` - возвращает функцию отмены горутин
+ `context.WithTimeout(parent, duration)` - так же возвращает функцию отмены, но так же сам отменяется через указанное время
+ `context.WithDeadline(parent, time.Time)` - Контекст с **конкретной датой и временем**, когда он будет отменён.
+ `context.WithValue(parent, key, value)` - Добавляет в контекст значение по ключу.