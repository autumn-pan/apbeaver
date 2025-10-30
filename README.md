# APBEAVER
This is just a repository for me to save my work on the Busy Beaver Function. I'm currently working on a Turing Machine simulator specialized for 6-state 2-symbol turing machines. In fact, the focus of my study is BB(6).

# Roadmap
Unaccelerated simulation has been added, but has not been tested on known halting machines. It also has not been expanded to comprehend certain syntax variants, which will be added in the near future. This is also unable to simulate a lot of more complex machines due to computational constraints. In one test, this system reached 36 billion steps in about 10 minutes on a BB6 holdout. The next goal is to create an accelerated simulator.

# Story
I was introduced to the Busy Beaver Function a few years ago by a friend. It was only this week that I learned that I could join the effort to research BB(6). When I first joined, I was encouraged to work on a TM simulator. I can run through billions of steps of turing machines with this code, but that is not enough in practice for many BB6 problems. 

This is APBeaver, an unaccelerated turing machine solver. It tracks the number of steps that a turing machine takes while directly simulating it. I made it using a large array of uint8_t, which represents symbols on a turing machine tape. The head is represented primarily by an index on the tape. The tape is essentially just a 4-kilobyte bitset. This was made with some basic knowledge about busy beaver, and it's not optimal yet. There are other representations that are more efficient which may be added in future versions. Currently, this is fine because it's just a base for what is to come.

This is important because it can decide if certain kinds of turing machines can reach their halt state. It works by manually going over every single step of a turing machine until it can't. I made it to act as a base to what would be an accelerated inductive turing machine simulator. The reason I'm working on the busy beaver problem is because I'm interested in it, and that the methods and technology we make to solve it will have meaningful contribution elsewhere. 

One challenge was building a robust parser, one that would be versatile and fail gracefully as opposed to some of my earlier projects. I added error checks and tried to follow best practice. I learned a lot about c standard practice, though this code isn't exactly safety-critical.

# Instructions
## Installation
```git clone https://github.com/autumn-pan/apbeaver```
## Execution
```./bb <turing_machine>```
Example:
```./bb 1RB1RD_0LB0LE_1LR1LC_1LA0LB_1LF1RE_---0RA```

[![Athena Award Badge](https://img.shields.io/endpoint?url=https%3A%2F%2Faward.athena.hackclub.com%2Fapi%2Fbadge)](https://award.athena.hackclub.com?utm_source=readme)
