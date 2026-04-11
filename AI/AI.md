# AI

--- 

## LLM 

A large language model is a complex statistical machine learning model trained on a large amount of data for recognizing patterns.

--- 

## Context & Context Window 

The **context** is a bank of information (tokens) the model uses for optimizing the responses. It can drastically improve the 
quality of the response if provided enough information. The **context window** is the amount of tokens the model can handle in one pass.

--- 

## Temperature

Is a parameter which determines how likely the model is to consider lower-probability tokens. The higher the temperature, the more likely.

--- 

## AI Skills 

- **Prompt Engineering**: process of giving an LLM context in a structured way to optimize outputs.
- **Building AI Agents**: create autonomous AI workflows for accomplishing certain tasks.
- **AI-Assisted Programming**: process of using specific techniques for partially automating mechanical writing of code.

--- 

## Skills AI cannot replace

AI is great at producing code, it does it fast, does not complain and with good practices it is actually usable.
But the tool is just as useful as skilled as its owner. Hence, these skills are necessary for any developer.

- **System Design**: We need to have domain knowledge, know how our system works, and why we choose some architecture over another. AI does not 
think; it is a prediction machine. Therefore, having knowledge about how the different parts of the system interact, what the trade-offs are, etc., is 
critical for the design of software applications.

- **Product Thinking**: We make products for humans, not machines (most of the time); hence, we have to be great at designing products 
and how they are going to be used, a good UI, and so on.

- **Security**: AI produces very insecure code; hence, knowledge about cybersecurity is crucial.

- **Performance**: Similar to security, the application can work, but if it's slow, then it is not going to be useful.

- **Legacy Knowledge**: Legacy code bases are mostly a combination of functional software and years of technical debt, which is not exactly AI-friendly.

- **Programming**: Programming is not about writing code; it is about problem solving, design, critical thinking, thinking out of the box, and understanding the inner workings of the code.
Also, a programmer who actually understands their languages and tools is way more effective than a vibecoder.

- **Reviewing**: Even with a coding agent in the reviewer role, it does not really understand the code and just compares it to its impression of the ideal book version, which differs from your use case.

--- 

## Explainable AI 



--- 

## Prompt Engineering

### Definition

Prompt engineering is the practice of **designing and refining inputs** (prompts) to guide large language models (LLMs) toward producing accurate, 
relevant, and useful outputs. It is a core skill in leveraging AI systems effectively.

### Uses

Prompt engineering is applied in multiple domains, including:

-   **Automation** – Streamlining workflows with precise task instructions.
-   **Content Generation** – Writing, summarization, and brainstorming.
-   **Data Analysis** – Extracting insights, cleaning, or transforming data.
-   **Education & Training** – Building interactive tutors or explanations.
-   **Prototyping** – Quickly testing ideas for applications using LLMs.

### 5 Steps Framework

-   **Task** - Define the objective clearly. Include specific instructions and a persona.
-   **Context** - Provide necessary background information.
-   **References** - Include examples or templates if applicable.
-   **Evaluate** - Set criteria for success.
-   **Iterate** - Refine the prompt based on output quality.

### How to Do It Properly

Effective prompt engineering involves:

1. **Clarity** – Use explicit and unambiguous language.
2. **Context** – Provide relevant background, examples, and constraints.
3. **Structure** – Use lists, steps, structure, or formatting for better comprehension.
4. **Iteration** – Test, refine, and adjust prompts based on results.
5. **Evaluation** – Compare outputs against desired outcomes.
6. **Persona** – Specify the role or style the model should adopt (e.g., "Act as a professional tutor").
7. **References** – Provide references and examples.

### Zero-Shot vs. Few-Shot

- **Zero-Shot**: The model is given a prompt without any examples. It relies solely on its pre-trained knowledge to generate a response.

- **Few-Shot**: The model is provided with a few examples in the prompt to guide its response. This helps the model understand the desired format or style.

### Hallucinations

LLMs sometimes produce **hallucinations**—outputs that are plausible-sounding but **factually incorrect or fabricated**.
Ways to mitigate hallucinations:

-   Ask the model to **cite sources** or show reasoning.
-   Use **verification steps** (cross-check with external data).
-   Keep prompts **specific** and avoid open-ended ambiguity.

### Best Practices

- **Be Specific** – Clear, detailed prompts yield better answers.
- **Use Examples** – Demonstrate desired output format or style.
- **Break Down Tasks** – Complex queries work better when split into smaller steps.
- **Iterate & Experiment** – Adjust wording, tone, and constraints.
- **Validate Outputs** – Always review results for accuracy and reliability.
- **Architecture** - Define the architecture and tech stack.

--- 

## Planning and Architecture 

Once requirements, architecture, and classes are defined, AI can be used to create diagrams, search for inaccuracies, and search for 
existing frameworks and libraries for eliminating workload from projects. 

--- 

## Typical Use Cases

- **Prototyping**: AI is great at creating rapid prototypes for UI and even for basic backend setup; we can create really fast and basic prototypes for 
first analysis of the requirement lists.

- **Repetitive Work**: When doing repetitive tasks like defining a function in a repository, which then is going to be more or less repeated in the service 
layer and finally called in the controller, these kinds of predictable patterns can be done quickly.

- **Search for Errors**: Simpler errors are quickly identifiable, but for complex logic errors or bad architectures it is not recommended. 

- **Tests**: Writing unit tests for classes, integration classes, and end-to-end tests for GUI. Unit tests are the recommended option; the other two can be too large-scale for 
AI to handle correctly.

- **Browser Automation**: Web scraping can also be accomplished by certain AI tools.

- **Code review**: Similar to error-searching, it can be helpful to use AI to get a second opinion on your code quality. Note: it works better with small pieces of code, 
and it also needs a lot of context for the use case. It can be wrong a lot of times; thus, be careful.

- **Documentation**: Auto-generate documentation. Works really well with individual classes and functions.

- **Grammar Correction**: This is mostly safe and has not a big impact on the document, if prompted to keep the original structure.

- **Refactoring**: Safe if prompted to keep the original structure and functionality.

- **API Specification**: Given the models and a description of the endpoints, the generation can be quite helpful.

--- 

## Define Rules
 
Each tool has its own format, but for Copilot we can define both `.instructions.md` and `.prompt.md` files, which help define rules, context, and prompts respectively.

- **Instructions**: Defines the rules, use-case, coding convention, etc for the code-base. 
- **Prompts**: Can be used to define prompts for regularly performed tasks like "write tests" and similar ones.

--- 

## Use Different Agents

Define agents for each of the tasks inside the codebase and, if possible, automate codependent agents to create workflows.

Typical Agents:

- **Code Reviewer**
- **Test Writer**
- **Implementation Planner**
- **Implementer**
- **Documenter**

--- 

## Spec Driven Development

It is based on describing to the agent the goal, and specific tech decisions, etc. in a structured document for generating the individual pieces of our
application. It is basically a framework of programming in natural language.

### Best Practices

- **Use a standard template**: Define a template for the structure of the specification: required fields, technology choices, user stories, etc. The format 
can vary depending on the type of software piece it is going to produce. This process can also be sped up and enhanced by the LLM with meta prompting.

- **Mirror structure**: Create a separate version of the file structure of the software, but with the specs instead of the actual source code files or at least textual 
descriptions of the original file. This is also an advantage in the sense of generating documentation.

- **Review**: Use your own technical knowledge to review the generated code and the quality improvements of the specifications made by the LLM.

### Templates

#### Feature Template

[Feature](./specs/Spec_template.md)

#### Implementation Plan Template

[Implementation Plan](./specs/Implementation_plan_template.md)

#### Task Template 

[Task](./specs/Task_template.md)

#### Constitution Template

[Constitution](./specs/Constitution_template.md)

### Workflow in Phases for Green Field Projects

- **Idea/Fix/Feature**: you have an idea either of large or small scope. Write it down and be specific. 

- **Requirements Analysis**: Write down the necessary requirements which derive from the first phase. 

- **Research**: Research the topic, techniques, practices, and the general know-how for how such a feature, fix, or even application is 
implemented in the best way possible. The results of the research are to be noted.

- **Design**: From the research, take decisions that best fit your needs and have good general feedback. Document the design in a Markdown document for 
the agent to follow. These are your methods.

- **Tasks/Specifications and Tests**: You have got the idea, requirements, and the methods documented in a structured way; proceed to define small 
tasks for the agent to implement. Write down the tasks in the specifications/documents the agent is going to use as input.

    - **Define Tests**: Into each of the tasks/specs always include the validation logic for the agent. This is meant to be a substask to be done after the 
    main implementation or, if using TDD, the other way around.

- **Implementation & Testing**: Run the tests to ensure the logic works correctly and correct if necessary manually or with an agent.

- **Review**: Always review the output of the agent carefully and understand each step of the code it has written; test it against your own design choices. 
This needs to be done by someone who knows the domain really well and for assistance and rapid feedback another agent for code review can also be used for reference.

- **Archive**: Always archive the documents generated during this process in a structured way, if possible also optimized for humans and AI. You want 
traceability built into your project.

### Workflow in Phases for Brown Field Projects

Most projects in the industry are not new, but consists on old messy codebases, which lack AI-friendliness. So to tackle this kind of 
situations the framework needs to be addapted. 

- **Specs Generation**: For each of the classes, make an LLM generate an Spec in you specific format, and also add you own knowledge or even 
writte the spec or file descriptions yourself. This is crucial to give the AI a strutured and compact way of working with the codebase.

- **Extensive Review**: Review each of the specs, user stories and descriptions for correctness. 

- **Use Phases of the Original Workflow**: From this point using the normal framework at a certain phase is not really a problem anymore. Note, 
that for very large projects, specs may be generated not all at once, but for only one specific part creating internal green fields.

### Limitations 

- **Cognitive Debt**: while AI can produce code very fast, we can only comprehend it at our own human pace. If you disconnect completely 
from the codebase, when things go wrong or you need to fix something critical, you are going to spend way more time than normal. No, an AI agent 
will not solve all of your problems: limited context window, non-deterministic, heavily dependent on its data. 

- **Technical Debt**: If no review is done on the output, then bad technical decisions also lead to poorly designed systems, thus making the application 
unsustainable on the long term. 

- **Size**: Once a project gets too big, no matter how well you structured the codebase, things are going to get messy and the interdependencies are 
going to become really complex. An AI cannot handle that, and a single human barely can, so cooperation between humans and agents is key.

- **Scope**: You cannot know every scenario your application is going to handle; hence, your specs can become obsolete very quickly, and the changes can lead 
to worse and worse code quality. 

- **Legacy Bases**: Existing codebases are not AI-friendly and sometimes not even human-friendly, so good luck using an AI in such a situation.

### How to Use Effectively

- **Small Tickets**: SDD is great for small tasks that do not require knowing the entire application. 

- **Boilerplate**: Generate boilerplate code for components, controllers, header files, etc.

- **Review Based on Conventions**: Use the agent to review your code based on the rules you or your team have set. 

- **Get Introspection of the Codebase**: Use the AI to get knowledge about the new codebase you have been given by dividing it into small domains. 

- **Tedious Refactoring**: Repetitive mechanical refactoring is a great task for an AI. 

- **Comment Level Documentation**: Once you have written a function or a medium-size file, tell the AI with some context to generate the documentation for it 
and review the results. 

--- 

## Agentic Workflow

An agentic workflow is a series of steps, instructions, tools, and one or multiple LLMs working together for accomplishing a specific task. 

- **LLMs**: The "brain" of the system; it makes decisions, uses tools, and communicates with other LLMs. 

- **Tools**: Scripts which define the necessary programs for accomplishing different tasks. They can be specified for each agent, 
so that they only access the necessary tools. 

- **Instructions**: Umbrella term for the context, instructions, conventions, output format, workflow, etc. written in Markdown. 

- **File Structure Template**:

```text 

/name_of_workflow 
        |_ .env
        |_ .tmp/ 
        |_ tool/
        |_ workflows/
        |_ CLAUDE.md
        |_ prompts/
```

--- 




