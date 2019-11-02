package main

import (
    "crypto/rand"
    "fmt"
    "math/big"
    "time"
)

type Int struct {
    int
}

func main() {
    var a Int
    c := make(chan interface{})

    go a.MutableSlowAssignment(1, c)
    go a.MutableSlowAssignment(2, c)

    <-c
    <-c
    fmt.Printf("%d\n", a.int)
}

func shouldWait() bool {
    // if err; r = zero
    r, _ := rand.Int(rand.Reader, big.NewInt(1))
    return r.Int64() == 0
}

func (a Int) SlowAssignment(value int, c chan interface{}) {
    if shouldWait() {
        time.Sleep(1 * time.Second)
    }
    a.int = value
    c<-nil
}

func (a *Int) MutableSlowAssignment(value int, c chan interface{}) {
    if shouldWait() {
        time.Sleep(1 * time.Second)
    }
    a.int = value
    c<-nil
}

