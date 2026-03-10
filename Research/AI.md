# AI For Software Development

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
7. **References** Provide references and examples.

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

Once requierements, architecture, classes are defined. AI can be used to create diagramms, search for inacuracies, search for 
existing frameworks, libraries for eliminating work load from the projects. 

--- 

## Typical Use Cases

- **Prototyping**: AI is great at creating rapid prototypes for UI and even for basic backend-setup, we can create really fast and basic prototypes for 
first analysis of the requierement lists.

- **Repetitive Work**: When doing Repetitive task like defining a function in a repository, which then is going to be more or less repeated in the service 
layer and finally called in the controller; these kind of predictable patterns can be done quickly.

- **Search for Errors**: Simpler erros are quickly identifiable but for complex logic errors or bad architectures is not recomended. 

- **Tests**: Writting Unit test for classes, integration classes and end-to-end for GUI. Unit tets are the recomended, the other two can to large scale for 
AI to handle correctly.

- **Browser Automation**: Webscrapping can also be accomplished by certain AI tools.

- **Code review**: Similar to error-searching, it can be helpful to use AI to get a second opinion for you code quality. Note, it works better with small pieces of code 
and it also needs a lot of context of the use. They can be wrong a lot of times, thus be careful.

- **Documentation**: Auto generate documentation. Works really well with indivual classes an functions.

- **Grammar Correction**: This is mostly safe and has not a big impact on the document, if prompted to keep the original structure.

- **Refactoring**: Safe if prompted to keep the original structure and functionality.

- **API Specification**: Given the models and a description of the endpoints, the generation can be quite helpful.

--- 

## Define Rules
 
Each tool has it own format but for copilot we can defined both `.instructions.md` and `.prompt.md` files which help to define rules, context and promts respectively.

- **Instructions**: Defines the rules, use-case, coding convention, etc for the code-base. 
- **Prompts**: Can be used to define prompts for regulary performed tasks like: "write tests" and simitlars.

--- 

## Use Different Agents

Define agents for each of the tasks inside the code base and if possible automate codependent agents to create workflows.

Typical Agents:

- **Code Reviewer**
- **Test Writter**
- **Implementation Planner**
- **Implementer**
- **Documenter**

--- 

