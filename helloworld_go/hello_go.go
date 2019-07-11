package main
/*
var x,y int
var (  // 这种因式分解关键字的写法一般用于声明全局变量
      a int
      b bool
    )

var c, d int = 1, 2
var e, f = 123, "hello"

//这种不带声明格式的只能在函数体中出现
//g, h := 123, "hello"
func main(){
  g, h := 123, "hello"
  println(x, y, a, b, c, d, e, f, g, h) 
  _, i, j := numbers()//接收的时候把第一个舍弃，直接收后两个
  println(i, j)
}

//x,y,a,b都是初始的值0，0，0，false
//剩下的都是经过初始化的值 

//用空白标识符接收函数的返回值
func numbers()(int, int, string){
  a, b, c := 1, 2, "zba"
  return a,b,c//函数返回值三个
}
*/ 

func main(){
  const (
    a = iota
    b
    c
    d
    e = "hh"
    f
    g = 100
    h 
    i = iota 
    j
  )
  println(a, b, c, d, e, f, g, h, i, j)
  const (
    w = 1 << iota 
    x = 3 << iota 
    y 
    z
  )
  println(w, x, y, z)
}
