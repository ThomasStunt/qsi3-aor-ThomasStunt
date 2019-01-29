# Age of Reason

We defined code easy to reason about as :

- Does not affect or mutate external state (ie : no side effects)
- Does not rely on external state
- Always return same output for a given input
- Have up to date documentation

## Goals of this training

- How a statically typed language with functional programming pattern could help ?
- How Type Driven Design and Test Driven Development could secure developments ?
- Discovery of ReasonML and Buckelscript

## Meet ReasonML

[Reason](https://reasonml.github.io/) is not a new language; it's a new syntax and toolchain powered by the battle-tested language, OCaml. Reason gives OCaml a familiar syntax geared toward JavaScript programmers.

Reason may compile to native app, ocaml byecode or JavaScript thanks to the project [BuckleScript](https://bucklescript.github.io), which compiles OCaml/Reason into readable JavaScript with smooth interop. Reason also compiles to fast, barebone assembly, thanks to OCaml itself.

You must now there is an alternative to BuckelScript which is named [Js_of_ocaml](http://ocsigen.org/js_of_ocaml/).

Both are great projects that have [different emphasys](https://bucklescript.github.io/docs/en/comparison-to-jsoo).

Js_of_ocaml promote more OCaml like coding style and is more interesting when you have a base code that may be compile to native and to js (libs) or to generate a JS front-end for an OCaml backend or - more interesting - to code tierless application with [Eliom](http://ocsigen.org/eliom/6.3/manual/intro)

Buckelscript promote more JS like coding style. It's really popular upon people that use ReasonML only to target javascript runtimes (node.js or browser). It's the choice for [ReasonReact](https://reasonml.github.io/reason-react/)

### First tour

Open the [try site](https://reasonml.github.io/en/try.html?reason=Q) and try each code bellow, step by step

#### Binding

Variable declaration and assignement use `let` binding :

```OCaml
let greeting : string = "hello";
let score : int = 10;
```

As you can see, syntax looks like Javascript with Flow (~‾▿‾)~

Bidings are immutables :

```OCaml
let greeting : string = "hello";
greeting = "bye"; /* Error : The value greeting is not an instance variable */
```

But you can wrap it with a ref, which is like a box whose content can change.

```OCaml
let score : ref(int) = ref(10);
score := 5;
let five : int = score^;
print_endline(string_of_int(five));
```

Except for some algorithms that are optimized in imperative programming, you should avoid to use mutable binding

However, you may create a new binding of the same name which shadows the previous binding :

```OCaml
let greeting : string = "hello";
print_endline(greeting); /* print hello */
let greeting : string = "bye";
print_endline(greeting); /* print bye */
```

#### Types

The type system is completely "sound". This means that, as long as your code compiles fine, every type guarantees that it's not lying about itself. In a conventional, best-effort type system, just because the type says it's e.g. "an integer that's never null", doesn't mean it's actually never null. In contrast, a pure Reason program has no null bugs.

ReasonML types can be inferred. The type system deduces the types for you even if you don't manually write them down.

```OCaml
let greeting = "hello";
let score = 10;
```

Alias types can refer to a type by a different name. They'll be equivalent:

```OCaml
type scoreType = int;
let score : scoreType = 10;
```

Reason provides two list primitives : List and Array

```OCaml
/* Lists are homogeneous, immutable, fast at prepending items */
let heroes : list(string) = ["Carl", "Rick", "Michonne"];
let moreHeroes = ["Negan", ...heroes]; /* spread operator like javascript */

/* Arrays are mutable, fast at random access & updates, fix-sized on native (flexibly sized on JavaScript) */
let heroesArray : array(string) = [|"Carl", "Rick", "Michonne"|];
let carl : string = heroesArray[0];
heroesArray[0] = "Negan";
```

Product types

```OCaml
/* Tuples are immutable, ordered, fix-sized at creation time heterogeneous */
let nameAndHeart: (string, int) = ("Negan", 10);
type coord3d = (int, int, int);
let warehouseCoord : coord3d = (1, 4, 18);

/* Records are immutable by default and fixed in field names and types */
type hero = {
  heart: int,
  name: string
};
let negan = {
    heart : 10,
    name : "Negan"
}
let name = "Carl";
let carl = {
    name, /* punning like javascript */
    heart : 8
}
```

Variant types

```OCaml
type lifeVariant =
  | Alive
  | Dead
  | Zombi;

let howAreYou = Alive;
```

Alive, Dead and Zombi are called "constructors" (or "tag"). The | bar separates each constructor. A variant's constructors need to be capitalized.

Variant comes with one of the most important features of Reason : **pattern matching**

```Ocaml
let message =
  switch (howAreYou) {
  | Zombi => "Aaaaaarg !"
  | Alive => "Great !"
  | Dead => "!!!"
  };
/* message is "Great!" */
```

#### Options

Reason itself doesn't have the notion of null or undefined. This is a great thing, as it wipes out an entire category of bugs. No more undefined is not a function, and cannot access foo of undefined!

We represent the existence and nonexistence of a value by wrapping it with the option type. Here's its definition from the standard library:

```Ocaml
type option('a) = None | Some('a)
```

It means "a value of type option is either None (nothing) or that actual value wrapped in a Some".

Exemple :

```Ocaml
type weapon = option(string);

let isDangerous = w => switch (w){
  | None => "not dangerous"
  | Some(a) => "is armed with a" ++ a
};

let unArmed:weapon = None;
let knife:weapon = Some("knife");

print_endline(isDangerous(unArmed));
print_endline(isDangerous(knife));
```

#### Functions

Functions are declared with an arrow and return the expression

```OCaml
let add : (int, int) => int = (x, y) => x + y;
let multiply = (x, y) => x * y; /* inference also works on function type */
add(1, 3); /* 4 */
```

ReasonML function are auto-curried. The above multiply is nothing but syntactic sugar for this

```OCaml
let multiply = (x) => (y) => x * y;
```

So Reason functions can automatically be partially called.

```OCaml
let multiply2 = multiply(2);
let ten = multiply2(5);
```

Another great feature is the pipe opertator which can compose function by piping them

```OCaml
let twenty = multiply2(5) |> multiply2; /* same as multiply2(multiply2(5))*/
let _ = (twenty |> string_of_int) |> print_endline /* same as print_endline(string_of_int(twenty)) */
```

After this overview we will start our first projet [Tennis Kata](./TENNIS.MD)
