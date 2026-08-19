# Continuous Integration (CI)

Continuous Integration (CI) is a software development practice where developers frequently merge their code changes into a shared repository, 
often multiple times a day. Each merge triggers an automated build and test process to detect integration issues early, ensuring faster feedback and 
higher software quality. 

The configuration files are just a glorified checklist of steps to be ran after each commit is pushed to an specific branch.

---

## Manual Setup 

Theoretically, we can emulate a platform like GitHub Actions locally on our machine, but this is not scalable for projects with other 
developers. In case you still want to set up a pipeline for the your project as a learning experience, then you can follow the following schema. 

1. Write a script which gets triggered every time a commit is triggered.

2. Launch a container with the necessary enviroment-components. 

3. Define a script with the commands to follow after a commit is made: running tests, checking integrity, building, etc. 

4. If you wish to do so, you can also set up a deployment pipe-line which will deliver the new code to the your customers. 

--- 

## Feature Driven Development

Agile framework in which software is planned and developed as a list of features. It can be mixed with classical 
scrum in the way that features are listed as items of the product backlog. It also allows for shorter release 
cycles by adding features in an incremental way.

--- 

## Goals

- **Feature Driven Development**:  By the nature of CI features are adaptable for different branches, isolated automatic test and versions lackig some non-critical features, allowing for 
compatibility for the following goals.

- **Automatic Tests**: New additions to the code base are automatically tested preventing unexpeted errors during the 
release, deployment etc.

- **Availability of demo and test-systems**: Funtional versions of the software are stored for delivery or demo purposes, securing 
the hability to show case the software at any point for the customer, even incomplete versions.

- **Increase of software quality**: Due to easier catch of errors, the version delivered to the customer has a less chance of containing 
bugs or undesired behavior. If errors somehow manage to get into the release version in some form of an edgecase, then they can be easily 
be integrated in the automatic tests expanding the coverage; thus, increasing the quality.

--- 

## Principles 

- **Shared Code Base:** Maintained via a version-control-system.

- **Automatic translation:** Standardized definition of tests, static checks by each integration. Prevents the "it works on my machine".

- **Automatic Distribution and Mirrors:** Division of distributions in **DEV**, **TEST** and **PROD**. Changes are tested.
in the production environment.

- **Frequent Integration:** Reduces the number of errors in the code-base. (Trunk-Based-Development).

- **Continuous Test Development:** For each change in the code, documentation and anaylsis there is a test or check.

- **Documentation:** Makes it easier for anybody to understand the product.

--- 

## Key Concepts of CI

- **Frequent Commits:** Developers integrate changes into the main branch frequently.

- **Automated Builds:** Code is compiled, packaged, and validated automatically.

- **Automated Testing:** Unit, integration, and regression tests run on every build.

- **Early Feedback:** Failures are detected quickly and resolved faster.

- **Collaboration:** Encourages team-wide ownership of code quality.

--- 

## Phases of CI

1. **Code Commit**:
   - Developers push code changes to a shared version control system (e.g., Git).
   - Trigger for the CI pipeline.

2. **Build Phase**:
   - Source code is compiled.
   - Dependencies are downloaded and packaged.
   - Artifacts (executables, libraries, containers) are generated.

3. **Test Phase**:
   - Unit tests run first to validate code logic.
   - Integration and regression tests ensure stability.
   - Security and static code analysis can be included.

4. **Feedback & Reporting**:
   - Results of builds/tests are shared with the team.
   - Developers receive notifications about failures.

5. **Artifact Management**:
   - Successful builds produce deployable artifacts stored in artifact repositories.

6. **Deployment (Optional in CI, mandatory in CD)**:
   - Artifacts are deployed to staging/test environments for validation.
   - If extended to **Continuous Deployment (CD)**, production deployment can be automated.


## Functions of CI

- **Automation of Builds & Tests:** Eliminates manual intervention, reduces errors.

- **Early Bug Detection:** Prevents accumulation of defects by testing frequently.

- **Improved Code Quality:** Enforces coding standards through linting & analysis.

- **Reduced Integration Risk:** Small incremental changes reduce integration conflicts.

- **Faster Delivery:** Streamlined pipelines accelerate release cycles.

- **Collaboration & Transparency:** CI dashboards and logs improve visibility.

--- 

## DevOps

Is a set of practices, tools, and a cultural philosophy that automate and integrate the processes between 
software development and IT operations teams.

### Phases and Tools 

- **Plan:** Jira, Common Sense
- **Code:** Git, GitHub, Nvim
- **Build:** Maven, Make, Cargo
- **Test:** Azure. (Quality Assurance, not code tests)  
- **Release:** Jenkins 
- **Deploy:**  Docker, Nix, Kubernetes
- **Operate:** CHEF, Ansible  
- **Monitor:** Grafana, Graylog

### Popular CI Tools

#### 1. **Jenkins**

- Open-source automation server.
- Highly customizable with plugins.
- Supports pipelines as code.

#### 2. **GitHub Actions**

- CI/CD built into GitHub repositories.
- Easy YAML-based workflows.
- Strong community integrations.

#### 3. **GitLab CI/CD**

- Integrated with GitLab platform.
- Built-in container registry.
- Supports auto DevOps pipelines.

#### 4. **CircleCI**

- Cloud-native CI/CD platform.
- Optimized for parallelization.
- Strong Docker support.

#### 5. **Travis CI**

- Hosted CI/CD service.
- Simple YAML-based configuration.
- Free for open-source projects.

#### 6. **Azure DevOps Pipelines**

- Microsoft’s CI/CD solution.
- Strong integration with Azure cloud.
- Multi-language and platform support.

--- 

## Example CI Workflow (GitHub Actions)

```yaml
# Example GitHub Actions CI Workflow
name: CI Pipeline

on: [push, pull_request]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout Code
        uses: actions/checkout@v3

      - name: Set up Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'

      - name: Install Dependencies
        run: npm install

      - name: Run Tests
        run: npm test
```

### Configurations Options

- ``:


### Best Practices in CI

- Commit small, frequent changes.
- Keep builds fast and reliable.
- Use version control for pipeline configurations.
- Run tests in parallel to reduce time.
- Fail fast: stop pipelines early when errors occur.
- Monitor pipeline health with dashboards.
- Secure the pipeline (secrets, dependencies, access).

--- 

## CI vs. CD


| Aspect         | Continuous Integration (CI) | Continuous Delivery/Deployment (CD) |
| -------------- | --------------------------- | ----------------------------------- |
| Focus          | Automating build & test     | Automating release & deployment     |
| Goal           | Detect integration issues   | Deliver software faster & safer     |
| Deployment     | Not always included         | Always included (staging/prod)      |
| Risk Reduction | Early bug detection         | Minimized release risk              |


---



