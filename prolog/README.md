# Fundamentals of Prolog

**Prolog** (*Programming in Logic*) is a logic programming language widely used in Artificial Intelligence (AI), knowledge representation, and natural language processing.  
Unlike procedural languages (e.g., Python, C, Java), Prolog is declarative — you define what is true, not how to compute it.

Prolog programs consist of **facts**, **rules**, and **queries** that describe relationships and logical inferences.

| Concept | Description | Example |
|----------|--------------|----------|
| **Fact** | Declares a basic truth about the world | `parent(john, mary).` |
| **Rule** | Defines a relationship using logic | `grandparent(X, Y) :- parent(X, Z), parent(Z, Y).` |
| **Query** | A question asked to the knowledge base | `?- grandparent(john, Who).` |
| **Variable** | Starts with a capital letter, represents an unknown | `X`, `Y`, `Person` |
| **Atom** | Lowercase identifiers (constants) | `john`, `pizza`, `blue` |
| **Backtracking** | Prolog automatically searches for all possible solutions | Use `;` to get more results in the interpreter |

## Applications of Prolog
Prolog is a powerful tool where problems can be expressed using a set of facts and rules:

- Expert Systems: It serves as the ideal engine for building knowledge-based systems that mimic human expertise. Knowledge is stored as logical rules, and Prolog's inference machine automatically draws conclusions.

- Natural Language Processing (NLP): Prolog's structure is perfectly suited for defining and executing formal grammars, such as Definite Clause Grammars (DCGs). This makes it highly effective for developing parsers and building the logic behind question-answering systems.

- Automated Theorem Proving: It is fundamentally designed to prove or disprove logical statements. Prolog uses a technique called backward chaining to logically verify complex queries based on existing facts and rules, which is crucial for verifying software specifications or logical consistency.

- Constraint Logic Programming (CLP): This advanced application combines Prolog's logic with specialized algorithms to solve optimization problems by working within defined constraints. It is widely used for complex scheduling and planning tasks.

## Advantages of Prolog
- Declarative Programming: Programs are written as a knowledge base of facts and rules, which is concise and high-level, allowing the programmer to focus on the logical structure of the problem domain rather than the step-by-step control flow.

- Automatic Search and Backtracking: The Prolog engine has a built-in mechanism that automatically searches for solutions and systematically backtracks when a path fails. This makes it exceptionally powerful for solving complex search, constraint satisfaction, and combinatorial problems.

- Ideal for Symbolic AI: It is the original language for symbolic Artificial Intelligence and is excellent for building expert systems, performing logical inference, and natural language processing due to its direct mapping to predicate logic.

- Rapid Prototyping: For problems that naturally fit the logic paradigm, the high-level syntax and automatic inference engine allow for very fast initial development and prototyping.

## Disadvantages of Prolog
- Slower Execution for Numeric Tasks: Since Prolog relies on its general-purpose logical inference engine, it is typically slower than imperative languages like C for purely computational or numeric-intensive tasks.

- Difficult Debugging and Flow Tracing: The program's execution order is implicitly determined by the logical structure and the backtracking algorithm. This can make it challenging for programmers to trace the exact flow and debug code, especially compared to the sequential nature of imperative languages.

- Steep Learning Curve: The required shift in mindset to think in terms of logic and relations (declarative vs. imperative thinking) presents a significant barrier to entry for many programmers.

- Limited Ecosystem and Industry Adoption: Prolog is a niche language, primarily used in academia and specific AI research. This means there is a much smaller pool of external libraries, tools, and community support compared to mainstream languages.

## Output of Prolog Queries
?- animal_lover(john)
|    .
true.

?- likes(sarah, What).
What = cat .

