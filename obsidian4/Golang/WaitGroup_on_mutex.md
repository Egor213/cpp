```go
package main

import (
	"fmt"
	"sync"
	"time"
)

// MyWaitGroup — аналог sync.WaitGroup на мьютексах
type MyWaitGroup struct {
	mu    sync.Mutex
	cond  *sync.Cond
	count int
}

func NewMyWaitGroup() *MyWaitGroup {
	wg := &MyWaitGroup{}
	wg.cond = sync.NewCond(&wg.mu)
	return wg
}

func (wg *MyWaitGroup) Add(n int) {
	wg.mu.Lock()
	defer wg.mu.Unlock()
	wg.count += n
}

func (wg *MyWaitGroup) Done() {
	wg.mu.Lock()
	defer wg.mu.Unlock()
	wg.count--
	if wg.count == 0 {
		wg.cond.Broadcast() // пробуждает всех, кто в Wait
	}
}

func (wg *MyWaitGroup) Wait() {
	wg.mu.Lock()
	defer wg.mu.Unlock()
	for wg.count > 0 {
		wg.cond.Wait() // обязательно Lock делать до
	}
}

```
