MASTER BUILD SPECIFICATION
CONTEXT ENGINE
Production-Ready, Open-Source, Local-First Data Analysis & Context Exploration System

ROLE

You are acting simultaneously as:

- Senior product engineer
- Senior full-stack engineer
- Data scientist
- Statistical software engineer
- Data-quality engineer
- Security engineer
- QA/test engineer
- UX/UI designer
- Open-source maintainer
- Technical architect

Your task is to BUILD Context Engine, not merely describe it.

Do not produce a superficial prototype, mock dashboard, static frontend, fake analysis, placeholder statistics, or an “AI-looking” interface.

Build a genuinely functioning application whose analytical results are produced by deterministic computational code.

==================================================
1. PRODUCT IDENTITY
==================================================

PRODUCT NAME:
Context Engine

CORE DESCRIPTION:

Context Engine is a local-first data analysis and context-exploration tool that turns raw datasets into evidence-graded research reports.

Its purpose is to help users understand:

1. What the numbers actually show.
2. What mathematical/statistical transformations reveal.
3. What relationships appear to exist.
4. What those relationships may suggest.
5. What the data cannot establish.
6. What real-world context the numbers are attached to.

The central intellectual principle is:

DATA → ANALYSIS → EVIDENCE → CONTEXT → INTERPRETATION

Never:

DATA → AUTOMATIC STORY

The system must preserve the distinction between evidence and interpretation.

==================================================
2. NON-NEGOTIABLE CORE PRINCIPLE
==================================================

Context Engine MUST function completely without an LLM or generative AI at runtime.

This is a hard architectural constraint.

DO NOT:

- require an LLM
- require an OpenAI API
- require an Anthropic API
- require a Gemini API
- require any generative AI provider
- use an LLM for statistical calculations
- use an LLM for validation
- use an LLM to determine statistical significance
- use an LLM to invent explanations
- use an LLM as the core analytical engine
- make the application unusable when no AI API key exists

The finished application must remain useful, reproducible, testable, and open source with ZERO model inference.

The AI builder may be used to generate the application's source code.

That does NOT mean the finished application should depend on AI.

Distinguish clearly between:

AI USED TO BUILD SOFTWARE

and

AI USED BY THE SOFTWARE.

Context Engine is allowed to be built using an AI builder but must not require an LLM to operate.

==================================================
3. OPTIONAL FUTURE AI
==================================================

If natural-language assistance is ever added, it must:

- be optional
- be disabled by default
- be isolated from the deterministic engine
- never replace deterministic computation
- never calculate statistics
- never become the source of truth
- never modify verified numerical results
- never invent dataset facts
- never silently introduce external information

The deterministic engine must remain fully functional if the AI layer is completely removed.

If an AI layer is added later, it may translate natural-language requests into a structured analysis specification.

Example:

USER:
“Compare average catch between coastal regions.”

OPTIONAL AI LAYER OUTPUT:

{
  "operation": "group_comparison",
  "group_column": "region",
  "target_column": "catch",
  "statistic": "mean"
}

The deterministic analysis engine then validates and executes that specification.

The LLM must NEVER directly produce the final numerical answer.

==================================================
4. PRODUCT VISION
==================================================

Build a serious, elegant, research-grade environment for exploring datasets in a way that connects statistics to real-world context.

The product should:

1. Ingest structured data.
2. Diagnose the dataset.
3. Detect data-quality problems.
4. Run deterministic statistical analysis.
5. Detect patterns and anomalies.
6. Test whether patterns remain robust under reasonable changes.
7. Attach findings to context labels.
8. Clearly distinguish evidence, association, inference, and unknowns.
9. Produce transparent, reproducible reports.
10. Allow users to inspect how every important finding was generated.

This must NOT feel like:

“Upload CSV → AI magically tells you what it means.”

It must feel like:

“Upload data → inspect data quality → investigate patterns → test findings → understand context → distinguish evidence from interpretation.”

==================================================
5. PRIMARY USERS
==================================================

Design for:

- Students
- Independent researchers
- Journalists
- Policy analysts
- Engineers
- Educators
- Open-source contributors
- Data analysts
- Researchers exploring unfamiliar datasets
- Anyone who wants to understand a dataset beyond surface-level charts

The application should not assume the user is a professional statistician.

Therefore:

- technical concepts should be explainable
- advanced methodology should remain available
- explanations must never replace methodological transparency
- users should be able to inspect the actual method used

==================================================
6. NON-GOALS
==================================================

Do NOT build:

- A chatbot-first product
- A generic chart generator
- A vague “AI data analyst”
- A causal inference system that pretends to know more than the data supports
- A login-required platform for the MVP
- A cloud-dependent application
- A black-box model that hides reasoning
- A system that silently changes user data
- A system that fabricates contextual information
- A system that treats correlation as causation
- A system that presents statistical output without methodological information

==================================================
7. MVP SCOPE
==================================================

The first production-quality MVP MUST support:

- CSV upload
- XLSX upload
- Automatic schema detection
- Column type inference
- Missing value detection
- Duplicate row detection
- Basic outlier detection
- Descriptive statistics
- Correlation analysis
- Group comparison analysis
- Time-series trend detection when dates exist
- Context tags for variables and findings
- Evidence labels for every claim
- HTML export
- PDF export
- JSON export
- Reproducible analysis logs
- Clean, polished UI

Do not remove any of these capabilities from the MVP.

==================================================
8. FUTURE CAPABILITIES
==================================================

Future support may include:

- JSON
- Parquet
- Geographic mapping
- More advanced anomaly detection
- Domain-specific context packs
- Collaborative sharing
- Optional plugin architecture

Do not allow future features to unnecessarily complicate the MVP.

==================================================
9. ARCHITECTURE
==================================================

Build Context Engine as a deterministic pipeline with clearly separated layers.

ARCHITECTURE:

INGESTION
    ↓
DIAGNOSIS
    ↓
ANALYSIS ENGINE
    ↓
CONTEXT ENGINE
    ↓
EVIDENCE ENGINE
    ↓
REPORT GENERATOR

The UI must not directly perform statistical calculations.

The frontend requests analysis from the backend/analysis engine.

The backend/analysis engine produces structured results.

The report generator consumes verified results.

==================================================
10. LAYER 1 — INGESTION
==================================================

Responsibilities:

- Accept file upload
- Validate file type
- Validate file size
- Parse file safely
- Detect encoding where relevant
- Detect delimiters for CSV
- Extract schema
- Infer initial data types
- Preserve original file unchanged

IMPORTANT:

Never overwrite the original uploaded dataset.

Maintain conceptual separation between:

ORIGINAL DATASET

CLEANED/TRANSFORMED DATASET

TRANSFORMATION LOG

The user must always be able to understand what changed.

No silent cleaning.

==================================================
11. LAYER 2 — DATA DIAGNOSIS
==================================================

Automatically identify:

- numerical variables
- categorical variables
- date/time variables
- likely identifiers
- likely geographic fields
- possible target variables
- missing values
- duplicate rows
- suspicious values
- impossible values where deterministic rules permit identification
- inconsistent data types
- potential unit ambiguity
- time coverage
- geographic coverage where detectable

Generate a DATASET HEALTH SUMMARY.

Example structure:

DATASET HEALTH

Rows:
Columns:
Time coverage:
Potential date fields:
Potential geographic fields:
Missing values:
Duplicate rows:
Suspicious values:
Potential ambiguities:

The diagnosis must report uncertainty where appropriate.

Do NOT claim a column is “income” merely because its name looks similar.

==================================================
12. LAYER 3 — ANALYSIS ENGINE
==================================================

Implement deterministic modules for:

A. DESCRIPTIVE ANALYSIS

- count
- mean
- median
- minimum
- maximum
- variance
- standard deviation
- quantiles
- distribution summaries

B. CORRELATION

Where statistically appropriate:

- Pearson
- Spearman

Clearly state which method was used.

Never describe correlation as proof of causation.

C. GROUP COMPARISON

Support appropriate comparisons between groups.

Show:

- group sizes
- relevant summary statistics
- effect/difference
- methodology
- limitations

D. TIME SERIES

When date/time variables exist:

- chronological trends
- rolling statistics
- period comparisons
- seasonality where appropriate
- anomalies
- change points where appropriately implemented

E. OUTLIER DETECTION

Support deterministic methods.

Clearly disclose:

- method
- threshold
- affected observations

Do not automatically delete outliers.

F. SUBGROUP ANALYSIS

Allow findings to be inspected across relevant groups.

This is important because aggregate relationships may hide subgroup differences.

G. SENSITIVITY CHECKS

Where applicable, test whether findings remain similar when:

- obvious outliers are excluded
- reasonable time windows change
- subgroup definitions change
- reasonable analytical specifications change

H. PATTERN ROBUSTNESS

A finding that disappears immediately under a reasonable alternative specification must not be presented as equally robust to one that persists.

==================================================
13. STATISTICAL INTEGRITY
==================================================

This is a core requirement.

The system must never automatically state:

“X caused Y”

merely because X and Y correlate.

Instead, use language such as:

“X and Y are statistically associated in the supplied dataset.”

or:

“The dataset shows a relationship between X and Y, but this analysis does not establish causality.”

Where causal inference is outside the supported methodology, explicitly say:

“Causality cannot be established from this analysis.”

The system should favor intellectual honesty over impressive-sounding conclusions.

==================================================
14. LAYER 4 — CONTEXT ENGINE
==================================================

Context Engine exists to answer:

“What are these numbers actually attached to?”

For every dataset, create a structured context profile containing, where available:

- domain
- geography
- time range
- affected people/groups
- institutions
- ecosystems
- economic factors
- policy factors
- social factors

The system must NOT invent contextual facts.

Context may come from:

1. The dataset itself.
2. Explicit user input.
3. User-provided external sources.

Do not silently browse the internet and treat retrieved information as fact.

If external information is introduced in a future version, it must be explicitly labeled EXTERNAL and include provenance.

==================================================
15. CONTEXT TAGGING
==================================================

Users should be able to attach context tags to:

- datasets
- columns
- variables
- findings
- reports

Examples:

ECOLOGY
ECONOMICS
POLICY
GEOGRAPHY
COMMUNITIES
SOCIAL
TEMPORAL
INSTITUTIONAL

The system should remain domain-agnostic.

Do not hardcode the product as a finance, climate, fisheries, or economics application.

The same architecture must work across domains.

==================================================
16. LAYER 5 — EVIDENCE ENGINE
==================================================

Every important conclusion must receive exactly one primary evidence classification:

OBSERVED

Directly visible or directly calculated from the supplied dataset.

DERIVED

Produced through a defined mathematical/statistical transformation.

ASSOCIATED

A statistical relationship has been identified.

INFERRED

A reasonable interpretation, but not directly established.

EXTERNAL

Information originating outside the supplied dataset.

UNKNOWN

The available evidence is insufficient.

These classifications must be implemented in the data model, not merely displayed as decorative UI text.

==================================================
17. EVIDENCE RULES
==================================================

Observed:
Directly calculated from the supplied data.

Derived:
Calculated from the supplied data through a documented transformation or method.

Associated:
A statistical relationship has been detected.

Inferred:
An interpretation that goes beyond direct observation.

External:
Information supplied by an external source.

Unknown:
Evidence is insufficient.

Never downgrade uncertainty merely to produce a more satisfying report.

==================================================
18. FINDING OBJECT MODEL
==================================================

Every finding should have structured fields equivalent to:

- finding_id
- title
- evidence_class
- value
- unit where known
- variables involved
- method
- parameters
- source_dataset
- source_rows or relevant subset where feasible
- confidence/uncertainty information where statistically appropriate
- caveat
- context_tags
- reproducibility metadata

The exact implementation may vary, but the underlying information must be preserved.

==================================================
19. LAYER 6 — REPORT GENERATOR
==================================================

Generate polished research reports containing:

1. Dataset summary
2. Data-quality issues
3. Key statistical findings
4. Visualizations
5. Context tags
6. Evidence labels
7. Methodology
8. Caveats
9. Reproducibility metadata
10. Export options

Every important finding should be traceable back to the analysis that produced it.

==================================================
20. FINDING UI
==================================================

Every finding must show:

- headline
- metric/value
- evidence label
- method used
- caveat
- relevant variables
- source rows or calculation details where feasible

The user must be able to answer:

“What exactly did the system calculate?”

without inspecting the source code.

==================================================
21. UX/UI
==================================================

The interface must feel:

- premium
- minimal
- serious
- research-oriented
- calm
- readable
- modern

Design principles:

- clean white mode
- dark mode support
- clear hierarchy
- elegant spacing
- strong typography
- obvious upload flow
- no clutter
- no fake “AI magic” language
- findings easy to read
- findings easy to verify

Avoid excessive gradients, meaningless animations, excessive glassmorphism, or visual effects that make the product look like a generic AI startup template.

The product should visually communicate trust and analytical seriousness.

==================================================
22. REQUIRED UI VIEWS
==================================================

Create:

1. Landing page
2. Dataset upload page
3. Dataset diagnosis page
4. Analysis dashboard
5. Context panel
6. Evidence panel
7. Report preview page
8. Export/download page

Navigation should be consistent.

Users must never become trapped inside a workflow.

Provide clear:

- Back
- Home
- Reset/New Analysis

actions where appropriate.

==================================================
23. DATA VISUALIZATION
==================================================

Visualizations must be analytical rather than decorative.

Charts must:

- use correct axes
- identify units
- display sample sizes where relevant
- avoid misleading scaling
- show missingness where relevant
- distinguish groups clearly
- provide readable labels
- remain accessible

Never create a chart simply because a chart looks impressive.

==================================================
24. ENGINEERING STACK
==================================================

Preferred stack:

FRONTEND:
- React
- TypeScript
- Tailwind CSS

BACKEND:
- Python
- FastAPI

DATA PROCESSING:
- Polars
- DuckDB

VISUALIZATION:
Use a reliable charting library appropriate for React.

REPORTING:
- HTML
- PDF
- JSON

STORAGE:
- local filesystem for MVP
- database only where genuinely necessary

AUTHENTICATION:
- none for MVP unless absolutely necessary

If the builder cannot use one of the preferred technologies, choose the closest robust alternative while preserving all architectural principles.

Do not introduce unnecessary infrastructure.

==================================================
25. ARCHITECTURE REQUIREMENTS
==================================================

The codebase must have:

- deterministic computation
- modular components
- typed interfaces
- clean separation between UI, API, and analysis logic
- no hidden side effects
- no silent data rewriting
- immutable original upload handling
- explicit transformation logs
- centralized validation
- predictable error handling

Avoid giant files containing the entire application.

Avoid duplicated business logic between frontend and backend.

Keep statistical logic isolated and testable.

==================================================
26. SECURITY
==================================================

Treat uploaded datasets as potentially sensitive.

Implement reasonable safeguards:

- validate uploaded files
- restrict accepted file types
- enforce file-size limits
- sanitize filenames
- avoid executing uploaded content
- never execute arbitrary uploaded code
- never expose server filesystem paths to users
- never log sensitive raw data unnecessarily
- never hardcode API keys
- never commit secrets
- isolate temporary files
- clean up temporary processing artifacts where appropriate

The application should not transmit uploaded data to third-party AI providers because the core system does not require them.

==================================================
27. OPEN-SOURCE REQUIREMENTS
==================================================

Make the project genuinely open source.

Repository must include:

- README
- installation instructions
- architecture overview
- contribution guide
- code of conduct
- security policy
- license
- sample datasets
- example outputs
- reproducible demo workflow
- documented roadmap

Recommended license:

Apache-2.0 or MIT.

Prefer Apache-2.0 if patent clarity is desired.

Open-source standards:

- no vendor lock-in
- no proprietary API requirement
- no hardcoded secrets
- easy local setup
- easy contribution path
- public roadmap
- understandable repository structure

==================================================
28. REPOSITORY STRUCTURE
==================================================

Use a clean structure similar to:

context-engine/

  apps/
    web/
    api/

  engine/
    ingestion/
    diagnosis/
    statistics/
    temporal/
    geography/
    context/
    evidence/
    reporting/

  tests/
    unit/
    integration/
    property/
    golden/

  datasets/
    examples/

  docs/

  README.md
  CONTRIBUTING.md
  CODE_OF_CONDUCT.md
  SECURITY.md
  LICENSE

Adapt this structure where necessary, but preserve clear separation of responsibilities.

==================================================
29. ANTI-BUG ENGINEERING
==================================================

The application must be designed to fail safely and predictably.

Implement:

- strict input validation
- schema checks
- file-size limits
- safe parsing
- clear error messages
- crash-resistant processing
- retry-safe workflows
- transformation logs
- reproducibility hashes
- typed data contracts
- unit tests
- integration tests
- property-based tests
- golden dataset tests
- CI checks
- linting
- formatting
- static type checking

Never silently recover from a potentially meaningful data error.

If a dataset cannot be analyzed safely, explain why.

==================================================
30. ERROR HANDLING
==================================================

Errors must be:

- human-readable
- technically meaningful
- actionable where possible

Bad:

“Something went wrong.”

Better:

“Column ‘date’ contains 14 values that could not be interpreted as dates. Analysis requiring chronological ordering was not run.”

Do not expose stack traces to ordinary users.

Keep detailed technical errors available for developers.

==================================================
31. TESTING
==================================================

Testing is mandatory, not optional.

Test:

- empty files
- malformed files
- massive files
- duplicate rows
- missing columns
- timezone/date edge cases
- inconsistent units
- extreme outliers
- mixed data types
- unexpected encodings
- columns with ambiguous meaning

==================================================
32. GOLDEN DATASETS
==================================================

Create known-answer datasets containing:

1. Simple correlation
2. No meaningful relationship
3. Strong outliers
4. Missing values
5. Time-series data
6. Hidden subgroup effect
7. A dataset where a misleading conclusion would be tempting

For every golden dataset, define expected outputs.

Example:

If:

X = [1,2,3,4,5]

Y = [2,4,6,8,10]

the expected Pearson correlation is approximately 1.

The test must verify the actual engine rather than trusting generated explanations.

==================================================
33. PROPERTY-BASED TESTING
==================================================

Use property-based testing where appropriate.

Test invariants such as:

- invalid data should not produce valid-looking results
- shuffled unrelated variables should not consistently generate strong relationships
- duplicate rows should behave according to the documented statistical method
- calculations should remain within mathematically valid bounds
- missing data must never silently become valid observations

Use an appropriate property-based testing framework.

==================================================
34. REPRODUCIBILITY
==================================================

Every analysis must have reproducibility metadata:

- dataset hash
- software version
- analysis version
- timestamp
- parameters
- methods
- report ID

Where possible, the user must be able to rerun the same dataset and analysis specification and obtain the same analytical result.

The only acceptable unavoidable variation should be presentation/layout variation, not numerical computation.

==================================================
35. ANALYSIS AUDIT TRAIL
==================================================

Maintain a clear chain:

RAW DATA
↓
VALIDATION
↓
TRANSFORMATION
↓
ANALYSIS
↓
STATISTICAL RESULT
↓
EVIDENCE CLASS
↓
CONTEXT
↓
REPORT

The user should be able to inspect this chain.

==================================================
36. REPORTING LANGUAGE
==================================================

Reports must sound like serious research software.

Always separate:

- what was observed
- what was calculated
- what was associated
- what was inferred
- what remains unknown

If the evidence does not support a claim, say so.

Never make a finding stronger merely because stronger wording sounds better.

==================================================
37. EXAMPLE OF DESIRED BEHAVIOR
==================================================

Suppose a dataset contains:

- location
- year
- fish species
- catch_kg
- water_temperature
- fishing_effort
- fuel_price

The system might find:

OBSERVED:
Catch declined 17% between two specified periods.

ASSOCIATED:
Water temperature and catch changed together over the same period.

ASSOCIATED:
Fishing effort also changed.

EXTERNAL:
A user-provided source reports a change in fuel prices.

INFERRED:
These factors may be relevant to the observed change.

UNKNOWN:
This dataset alone does not establish that temperature caused the catch decline.

The system must NOT output:

“Temperature caused the fisheries decline.”

unless the user has supplied an appropriate causal design and the implemented methodology genuinely supports that conclusion.

==================================================
38. PRIVACY PRINCIPLE
==================================================

Because Context Engine is local-first:

Prefer processing data locally whenever possible.

The MVP should not require users to upload datasets to a remote third-party service merely to perform ordinary statistical analysis.

The product's core functionality should work offline after installation if the chosen stack permits it.

==================================================
39. PERFORMANCE
==================================================

Do not optimize prematurely, but design the architecture so that large datasets do not unnecessarily freeze the browser.

Heavy analysis should occur in the backend/processing layer rather than directly in the UI.

The UI should communicate processing states clearly:

- Uploading
- Validating
- Profiling
- Analyzing
- Testing
- Generating report
- Complete

Never make users wonder whether the application has frozen.

==================================================
40. FUTURE CONTEXT PACKS
==================================================

Design the Context Engine so future contributors can create domain-specific context packs.

Possible future packs:

- fisheries
- climate
- economics
- urban mobility
- agriculture
- education
- environmental science

A context pack may eventually define:

- relevant variables
- common statistical questions
- known analytical pitfalls
- recommended visualizations
- terminology
- domain-specific warnings

Do not hardcode these future packs into the MVP unless required.

==================================================
41. DEVELOPMENT PHASES
==================================================

Build in controlled phases.

PHASE 1 — FOUNDATION

Implement:

- project structure
- frontend
- backend
- upload flow
- CSV/XLSX parsing
- schema detection
- profiling
- basic statistics
- basic report

Do not move forward until this works reliably.

PHASE 2 — ANALYSIS

Implement:

- correlations
- group comparisons
- time-series support
- subgroup analysis
- anomaly detection
- robustness checks
- sensitivity analysis

PHASE 3 — EVIDENCE + CONTEXT

Implement:

- evidence classifications
- context tags
- context profiles
- traceability
- caveats
- report evidence sections

PHASE 4 — REPRODUCIBILITY

Implement:

- hashes
- analysis IDs
- analysis metadata
- versioning
- reproducible reports
- JSON export

PHASE 5 — TESTING + HARDENING

Implement:

- unit tests
- integration tests
- property tests
- golden datasets
- malformed-input tests
- performance testing
- security review
- CI

PHASE 6 — POLISH

Implement:

- final UI
- accessibility
- responsive design
- error states
- loading states
- documentation
- onboarding
- report design

PHASE 7 — OPEN-SOURCE RELEASE

Prepare:

- README
- installation
- architecture documentation
- contributing guide
- license
- security policy
- examples
- sample datasets
- roadmap

==================================================
42. DEVELOPMENT DISCIPLINE
==================================================

Do NOT build everything in one giant pass and then claim completion.

After each major phase:

1. Run the application.
2. Test the relevant workflows.
3. Inspect errors.
4. Fix failures.
5. Run tests.
6. Confirm existing functionality still works.
7. Only then continue.

Never sacrifice existing functionality merely to add a new feature.

Avoid introducing unnecessary dependencies.

==================================================
43. NO FAKE FUNCTIONALITY
==================================================

This is a strict rule.

Do NOT:

- fake analysis
- hardcode sample results into production paths
- create buttons that do nothing
- create fake export functionality
- display placeholder statistics as if they were real
- claim a test exists if it does not
- claim reproducibility without metadata
- label an inference as an observation
- pretend a feature is implemented when it is only mocked

If a feature cannot yet be implemented correctly, expose the limitation clearly rather than faking it.

==================================================
44. DEFINITION OF DONE
==================================================

Context Engine is not complete until:

- users can upload datasets
- CSV works
- XLSX works
- schema detection works
- data profiling works
- missingness detection works
- duplicate detection works
- outlier detection works
- descriptive analysis works
- correlation analysis works
- group comparisons work
- time-series analysis works where applicable
- evidence labels are implemented
- context tagging works
- reports can be generated
- HTML export works
- PDF export works
- JSON export works
- reproducibility metadata exists
- analysis logs exist
- errors are handled safely
- tests exist and pass
- golden datasets exist
- the application works without an LLM
- the application does not require a proprietary AI API
- the application can run locally
- the repository is open-source ready
- documentation exists
- the codebase is understandable to contributors

==================================================
45. FINAL ARCHITECTURAL CHECK
==================================================

Before producing or modifying code, perform an internal architecture review.

Check specifically for:

1. Contradictory requirements
2. Hidden dependencies
3. Unnecessary complexity
4. Accidental LLM dependencies
5. Non-deterministic calculations
6. Silent data transformations
7. Unsupported causal claims
8. Missing error states
9. Missing validation
10. Missing tests
11. Security weaknesses
12. Privacy weaknesses
13. Reproducibility gaps
14. Poor separation of concerns
15. Frontend/backend duplication
16. Fake or incomplete functionality
17. Unnecessary infrastructure
18. Features outside MVP scope

If a conflict exists, prioritize in this order:

1. Data integrity
2. Statistical correctness
3. Reproducibility
4. Security/privacy
5. Deterministic behavior
6. Testability
7. Open-source maintainability
8. Usability
9. Visual polish
10. Convenience

==================================================
46. FINAL PRODUCT PRINCIPLE
==================================================

Context Engine should embody one central idea:

DATA DOES NOT SPEAK FOR ITSELF.

Numbers require:

- measurement
- methodology
- context
- skepticism
- interpretation

The product should help users explore that boundary without pretending to eliminate uncertainty.

The goal is not to produce the most confident answer.

The goal is to produce the most defensible answer supported by the available evidence.

==================================================
47. FINAL EXECUTION INSTRUCTION
==================================================

Build the application.

Do not merely explain how it could be built.

Do not return a superficial mockup.

Do not substitute an LLM for deterministic functionality.

Do not omit requirements because they are inconvenient.

Do not silently simplify away any requirement above.

Before implementation, internally reconcile the specification and create a coherent architecture.

Then implement incrementally according to the development phases.

After each phase, test the application and fix failures before proceeding.

Keep the core:

- deterministic
- local-first
- reproducible
- statistically responsible
- privacy-conscious
- secure
- open-source
- modular
- testable
- maintainable

The finished Context Engine must be capable of standing entirely on its own without an LLM at runtime.

==================================================
IMPLEMENTATION — CONTEXT ENGINE
==================================================

PROJECT STRUCTURE
==================================================

context-engine/
├── README.md
├── LICENSE
├── CONTRIBUTING.md
├── CODE_OF_CONDUCT.md
├── SECURITY.md
├── pyproject.toml
├── package.json
├── requirements.txt
│
├── apps/
│   ├── web/
│   │   ├── package.json
│   │   ├── tsconfig.json
│   │   ├── tailwind.config.js
│   │   ├── postcss.config.js
│   │   ├── src/
│   │   │   ├── index.tsx
│   │   │   ├── App.tsx
│   │   │   ├── pages/
│   │   │   │   ├── Landing.tsx
│   │   │   │   ├── Upload.tsx
│   │   │   │   ├── Diagnosis.tsx
│   │   │   │   ├── Analysis.tsx
│   │   │   │   ├── Report.tsx
│   │   │   │   └── Export.tsx
│   │   │   ├── components/
│   │   │   │   ├── Navigation.tsx
│   │   │   │   ├── FileUploader.tsx
│   │   │   │   ├── DataGrid.tsx
│   │   │   │   ├── Chart.tsx
│   │   │   │   ├── Finding.tsx
│   │   │   │   ├── ContextPanel.tsx
│   │   │   │   ├── EvidencePanel.tsx
│   │   │   │   └── LoadingState.tsx
│   │   │   ├── api/
│   │   │   │   └── client.ts
│   │   │   ├── types/
│   │   │   │   └── index.ts
│   │   │   └── styles/
│   │   │       └── globals.css
│   │
│   └── api/
│       ├── main.py
│       ├── requirements.txt
│       ├── config.py
│       ├── src/
│       │   ├── __init__.py
│       │   ├── ingestion/
│       │   │   ├── __init__.py
│       │   │   ├── parser.py
│       │   │   ├── validator.py
│       │   │   └── schema.py
│       │   ├── diagnosis/
│       │   │   ├── __init__.py
│       │   │   ├── profiler.py
│       │   │   └── health.py
│       │   ├── statistics/
│       │   │   ├── __init__.py
│       │   │   ├── descriptive.py
│       │   │   ├── correlation.py
│       │   │   ├── comparison.py
│       │   │   └── outlier.py
│       │   ├── temporal/
│       │   │   ├── __init__.py
│       │   │   └── timeseries.py
│       │   ├── context/
│       │   │   ├── __init__.py
│       │   │   └── context_engine.py
│       │   ├── evidence/
│       │   │   ├── __init__.py
│       │   │   └── evidence.py
│       │   └── reporting/
│       │       ├── __init__.py
│       │       ├── reporter.py
│       │       └── exporters.py
│       └── routes/
│           ├── __init__.py
│           ├── upload.py
│           ├── analysis.py
│           └── export.py
│
├── engine/
│   ├── __init__.py
│   ├── core.py
│   ├── pipeline.py
│   └── types.py
│
├── tests/
│   ├── unit/
│   │   ├── test_parser.py
│   │   ├── test_validator.py
│   │   ├── test_statistics.py
│   │   └── test_evidence.py
│   ├── integration/
│   │   └── test_pipeline.py
│   ├── property/
│   │   └── test_properties.py
│   └── golden/
│       ├── test_golden.py
│       └── datasets/
│           ├── simple_correlation.csv
│           ├── no_relationship.csv
│           ├── with_outliers.csv
│           ├── with_missing.csv
│           └── timeseries.csv
│
├── datasets/
│   └── examples/
│       ├── fisheries_sample.csv
│       ├── temperature_sample.csv
│       └── README.md
│
└── docs/
    ├── ARCHITECTURE.md
    ├── API.md
    ├── CONTRIBUTING.md
    └── ROADMAP.md

==================================================
PHASE 1: FOUNDATION — CORE DATA TYPES
==================================================

File: engine/types.py

"""
Core data type definitions for Context Engine.
"""

from typing import Any, Dict, List, Optional, Literal
from enum import Enum
from dataclasses import dataclass, field
from datetime import datetime

class DataType(str, Enum):
    NUMERIC = "numeric"
    CATEGORICAL = "categorical"
    DATETIME = "datetime"
    IDENTIFIER = "identifier"
    UNKNOWN = "unknown"

class EvidenceClass(str, Enum):
    OBSERVED = "observed"
    DERIVED = "derived"
    ASSOCIATED = "associated"
    INFERRED = "inferred"
    EXTERNAL = "external"
    UNKNOWN = "unknown"

@dataclass
class ColumnProfile:
    """Profile of a single column."""
    name: str
    data_type: DataType
    sample_values: List[Any]
    null_count: int
    null_percentage: float
    unique_count: int
    cardinality_ratio: float
    sample_size: int

@dataclass
class DatasetHealth:
    """Overall health assessment of a dataset."""
    row_count: int
    column_count: int
    columns: Dict[str, ColumnProfile]
    time_coverage: Optional[str]
    potential_date_fields: List[str]
    potential_geographic_fields: List[str]
    total_missing_values: int
    duplicate_rows: int
    suspicious_values: List[Dict[str, Any]]
    potential_ambiguities: List[str]
    assessment_timestamp: datetime = field(default_factory=datetime.utcnow)

@dataclass
class Finding:
    """Represents a single analytical finding."""
    finding_id: str
    title: str
    evidence_class: EvidenceClass
    value: Any
    unit: Optional[str] = None
    variables_involved: List[str] = field(default_factory=list)
    method: str = ""
    parameters: Dict[str, Any] = field(default_factory=dict)
    source_dataset_name: str = ""
    source_rows: Optional[List[int]] = None
    confidence_interval: Optional[tuple] = None
    caveat: Optional[str] = None
    context_tags: List[str] = field(default_factory=list)
    reproducibility_hash: Optional[str] = None
    timestamp: datetime = field(default_factory=datetime.utcnow)

@dataclass
class AnalysisResult:
    """Container for complete analysis results."""
    dataset_name: str
    dataset_hash: str
    software_version: str
    analysis_timestamp: datetime
    dataset_health: DatasetHealth
    findings: List[Finding]
    transformation_log: List[str]
    reproducibility_id: str
    analysis_parameters: Dict[str, Any]

==================================================
PHASE 1: FOUNDATION — CORE PIPELINE
==================================================

File: engine/core.py

"""
Core pipeline orchestrator.
"""

import hashlib
import uuid
from datetime import datetime
from typing import Tuple, Optional
import polars as pl

from engine.types import (
    DatasetHealth,
    AnalysisResult,
    ColumnProfile,
    DataType,
)

class CorePipeline:
    """
    Main analysis pipeline orchestrator.
    Maintains clean separation between ingestion, diagnosis, and analysis.
    """

    def __init__(self):
        self.version = "0.1.0"
        self.transformation_log: List[str] = []
        self.original_dataframe: Optional[pl.DataFrame] = None
        self.working_dataframe: Optional[pl.DataFrame] = None
        self.dataset_hash: Optional[str] = None
        self.reproducibility_id: str = str(uuid.uuid4())

    def ingest(self, dataframe: pl.DataFrame, dataset_name: str) -> Tuple[str, str]:
        """
        Ingest dataset and preserve original.
        Returns: (dataset_hash, dataset_name)
        """
        self.original_dataframe = dataframe.clone()
        self.working_dataframe = dataframe.clone()
        
        # Generate hash of original data
        parquet_bytes = self.original_dataframe.write_parquet()
        self.dataset_hash = hashlib.sha256(parquet_bytes).hexdigest()
        
        self.transformation_log.append(
            f"[{datetime.utcnow().isoformat()}] Dataset ingested: {dataset_name} ({self.original_dataframe.shape[0]} rows, {self.original_dataframe.shape[1]} columns)"
        )
        
        return self.dataset_hash, dataset_name

    def diagnose(self) -> DatasetHealth:
        """
        Run comprehensive data diagnosis.
        """
        if self.original_dataframe is None:
            raise ValueError("No dataset loaded")

        df = self.original_dataframe
        health = DatasetHealth(
            row_count=df.shape[0],
            column_count=df.shape[1],
            columns={},
            time_coverage=None,
            potential_date_fields=[],
            potential_geographic_fields=[],
            total_missing_values=0,
            duplicate_rows=0,
            suspicious_values=[],
            potential_ambiguities=[],
        )

        # Profile each column
        for col_name in df.columns:
            profile = self._profile_column(df, col_name)
            health.columns[col_name] = profile
            health.total_missing_values += profile.null_count

        # Detect duplicate rows
        health.duplicate_rows = (df.shape[0] - df.unique().shape[0])

        # Detect potential date fields
        health.potential_date_fields = self._detect_date_fields(df)
        
        # Detect potential geographic fields
        health.potential_geographic_fields = self._detect_geographic_fields(df)

        # Assess time coverage if dates exist
        if health.potential_date_fields:
            health.time_coverage = self._assess_time_coverage(df, health.potential_date_fields)

        self.transformation_log.append(
            f"[{datetime.utcnow().isoformat()}] Data diagnosis completed"
        )

        return health

    def _profile_column(self, df: pl.DataFrame, col_name: str) -> ColumnProfile:
        """Profile a single column."""
        col_data = df[col_name]
        null_count = col_data.null_count()
        sample_size = df.shape[0]
        unique_count = col_data.n_unique()
        
        # Infer data type
        inferred_type = self._infer_type(col_data)
        
        # Get sample values (up to 5)
        sample_values = col_data.drop_nulls().head(5).to_list()
        
        return ColumnProfile(
            name=col_name,
            data_type=inferred_type,
            sample_values=sample_values,
            null_count=null_count,
            null_percentage=(null_count / sample_size * 100) if sample_size > 0 else 0,
            unique_count=unique_count,
            cardinality_ratio=(unique_count / sample_size) if sample_size > 0 else 0,
            sample_size=sample_size,
        )

    def _infer_type(self, col: pl.Series) -> DataType:
        """Infer the data type of a column."""
        dtype = col.dtype
        
        if dtype in [pl.Float32, pl.Float64, pl.Int8, pl.Int16, pl.Int32, pl.Int64]:
            return DataType.NUMERIC
        elif dtype in [pl.Date, pl.Datetime]:
            return DataType.DATETIME
        elif dtype == pl.Utf8:
            # Heuristic: high cardinality might indicate identifier
            if col.n_unique() / col.shape[0] > 0.95:
                return DataType.IDENTIFIER
            return DataType.CATEGORICAL
        else:
            return DataType.UNKNOWN

    def _detect_date_fields(self, df: pl.DataFrame) -> List[str]:
        """Detect potential date/time fields."""
        date_fields = []
        for col_name in df.columns:
            if df[col_name].dtype in [pl.Date, pl.Datetime]:
                date_fields.append(col_name)
        return date_fields

    def _detect_geographic_fields(self, df: pl.DataFrame) -> List[str]:
        """Detect potential geographic fields by name heuristics."""
        geo_keywords = ['lat', 'long', 'latitude', 'longitude', 'country', 'region', 'state', 'city', 'location', 'geography']
        geo_fields = []
        
        for col_name in df.columns:
            col_lower = col_name.lower()
            if any(keyword in col_lower for keyword in geo_keywords):
                geo_fields.append(col_name)
        
        return geo_fields

    def _assess_time_coverage(self, df: pl.DataFrame, date_fields: List[str]) -> Optional[str]:
        """Assess time coverage if date fields exist."""
        if not date_fields:
            return None
        
        date_col = date_fields[0]
        try:
            min_date = df[date_col].min()
            max_date = df[date_col].max()
            return f"{min_date} to {max_date}"
        except:
            return None

    def get_analysis_result(self, findings: List) -> AnalysisResult:
        """Package complete analysis result."""
        if self.dataset_health is None:
            raise ValueError("Must run diagnosis before generating analysis result")
        
        return AnalysisResult(
            dataset_name=self.dataset_name,
            dataset_hash=self.dataset_hash,
            software_version=self.version,
            analysis_timestamp=datetime.utcnow(),
            dataset_health=self.dataset_health,
            findings=findings,
            transformation_log=self.transformation_log,
            reproducibility_id=self.reproducibility_id,
            analysis_parameters={},
        )

==================================================
PHASE 1: FOUNDATION — INGESTION LAYER
==================================================

File: apps/api/src/ingestion/parser.py

"""
Ingestion layer: file parsing and loading.
"""

import io
from typing import Tuple, Optional
import polars as pl

class FileParser:
    """Parse uploaded files safely."""

    ALLOWED_FORMATS = {'csv', 'xlsx'}
    MAX_FILE_SIZE = 100 * 1024 * 1024  # 100 MB

    @staticmethod
    def parse_file(file_content: bytes, filename: str) -> Tuple[pl.DataFrame, str]:
        """
        Parse uploaded file and return DataFrame and detected encoding.
        
        Args:
            file_content: Raw file bytes
            filename: Original filename
            
        Returns:
            Tuple of (DataFrame, detected_format)
            
        Raises:
            ValueError: If file format unsupported or parsing fails
        """
        
        # Validate file size
        if len(file_content) > FileParser.MAX_FILE_SIZE:
            raise ValueError(f"File exceeds maximum size of {FileParser.MAX_FILE_SIZE / 1024 / 1024}MB")

        # Extract extension
        file_ext = filename.split('.')[-1].lower()
        
        if file_ext not in FileParser.ALLOWED_FORMATS:
            raise ValueError(f"Unsupported file format: {file_ext}. Supported: {FileParser.ALLOWED_FORMATS}")

        try:
            if file_ext == 'csv':
                return FileParser._parse_csv(file_content), 'csv'
            elif file_ext == 'xlsx':
                return FileParser._parse_xlsx(file_content), 'xlsx'
        except Exception as e:
            raise ValueError(f"Failed to parse {file_ext} file: {str(e)}")

    @staticmethod
    def _parse_csv(content: bytes) -> pl.DataFrame:
        """Parse CSV with automatic delimiter detection."""
        
        # Try UTF-8 first
        try:
            text = content.decode('utf-8')
        except UnicodeDecodeError:
            # Try common alternatives
            for encoding in ['latin-1', 'iso-8859-1', 'cp1252']:
                try:
                    text = content.decode(encoding)
                    break
                except:
                    continue
            else:
                raise ValueError("Could not detect file encoding")

        # Try to detect delimiter
        first_line = text.split('\n')[0]
        delimiter = FileParser._detect_delimiter(first_line)

        # Parse with polars
        df = pl.read_csv(io.StringIO(text), separator=delimiter)
        return df

    @staticmethod
    def _parse_xlsx(content: bytes) -> pl.DataFrame:
        """Parse XLSX file."""
        df = pl.read_excel(io.BytesIO(content))
        return df

    @staticmethod
    def _detect_delimiter(line: str) -> str:
        """Detect CSV delimiter."""
        common_delimiters = [',', ';', '\t', '|']
        delimiter_counts = {delim: line.count(delim) for delim in common_delimiters}
        return max(delimiter_counts, key=delimiter_counts.get)

==================================================
PHASE 1: FOUNDATION — VALIDATION LAYER
==================================================

File: apps/api/src/ingestion/validator.py

"""
Validation layer: ensure data safety and integrity.
"""

from typing import List, Tuple
import polars as pl

class FileValidator:
    """Validate files before processing."""

    @staticmethod
    def validate_dataframe(df: pl.DataFrame, filename: str) -> Tuple[bool, List[str]]:
        """
        Validate that a parsed DataFrame is safe to process.
        
        Returns:
            Tuple of (is_valid, list_of_warnings)
        """
        warnings = []

        if df.shape[0] == 0:
            return False, ["Dataset contains no rows"]

        if df.shape[1] == 0:
            return False, ["Dataset contains no columns"]

        # Check for problematic column names
        for col in df.columns:
            if not col or len(col) == 0:
                warnings.append("Dataset contains empty column names")
            if len(col) > 255:
                warnings.append(f"Column name exceeds 255 characters: {col[:50]}...")

        # Check data types can be reasonably inferred
        for col in df.columns:
            if df[col].dtype == pl.Unknown:
                warnings.append(f"Column '{col}' has unknown data type")

        return True, warnings

==================================================
PHASE 1: FOUNDATION — SCHEMA DETECTION
==================================================

File: apps/api/src/ingestion/schema.py

"""
Schema detection: infer and record dataset structure.
"""

from typing import Dict
import polars as pl

class SchemaDetector:
    """Detect and document dataset schema."""

    @staticmethod
    def detect_schema(df: pl.DataFrame) -> Dict:
        """
        Detect and return schema information.
        """
        schema = {
            "columns": [],
            "column_count": df.shape[0],
            "row_count": df.shape[1],
        }

        for col_name in df.columns:
            col_dtype = df[col_name].dtype
            schema["columns"].append({
                "name": col_name,
                "type": str(col_dtype),
                "nullable": df[col_name].null_count() > 0,
            })

        return schema

==================================================
PHASE 1: FOUNDATION — FASTAPI APPLICATION
==================================================

File: apps/api/main.py

"""
FastAPI application - main entry point.
"""

from fastapi import FastAPI, UploadFile, File, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from typing import Dict, Any
import polars as pl

from src.ingestion.parser import FileParser
from src.ingestion.validator import FileValidator
from engine.core import CorePipeline

app = FastAPI(
    title="Context Engine API",
    version="0.1.0",
    description="Local-first data analysis and context exploration system"
)

# Enable CORS for local development
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000", "http://localhost:5173"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Global pipeline instance (simplified; real app would use session management)
pipeline = CorePipeline()

@app.on_event("startup")
async def startup():
    """Initialize on startup."""
    print("Context Engine API starting...")

@app.post("/api/upload")
async def upload_dataset(file: UploadFile = File(...)) -> Dict[str, Any]:
    """
    Upload and ingest dataset.
    
    Returns:
        Dataset metadata and initial health assessment
    """
    try:
        # Read file
        content = await file.read()
        
        # Parse
        df, file_format = FileParser.parse_file(content, file.filename)
        
        # Validate
        is_valid, warnings = FileValidator.validate_dataframe(df, file.filename)
        if not is_valid:
            raise HTTPException(status_code=400, detail=f"Invalid file: {warnings[0]}")
        
        # Ingest into pipeline
        dataset_hash, dataset_name = pipeline.ingest(df, file.filename)
        
        # Run diagnosis
        health = pipeline.diagnose()
        
        return {
            "success": True,
            "dataset_name": dataset_name,
            "dataset_hash": dataset_hash,
            "reproducibility_id": pipeline.reproducibility_id,
            "row_count": health.row_count,
            "column_count": health.column_count,
            "warnings": warnings,
            "health": {
                "total_missing": health.total_missing_values,
                "duplicate_rows": health.duplicate_rows,
                "time_coverage": health.time_coverage,
            }
        }
        
    except FileParser.ParseError as e:
        raise HTTPException(status_code=400, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Upload failed: {str(e)}")

@app.get("/api/health")
async def health_check() -> Dict[str, Any]:
    """Health check endpoint."""
    return {
        "status": "healthy",
        "version": "0.1.0",
        "service": "Context Engine API"
    }

@app.get("/api/dataset/diagnosis")
async def get_diagnosis() -> Dict[str, Any]:
    """
    Get full diagnosis of loaded dataset.
    """
    if pipeline.original_dataframe is None:
        raise HTTPException(status_code=400, detail="No dataset loaded")
    
    health = pipeline.diagnose()
    
    return {
        "row_count": health.row_count,
        "column_count": health.column_count,
        "columns": {
            name: {
                "type": profile.data_type.value,
                "null_count": profile.null_count,
                "null_percentage": profile.null_percentage,
                "unique_count": profile.unique_count,
                "cardinality": profile.cardinality_ratio,
                "sample_values": profile.sample_values,
            }
            for name, profile in health.columns.items()
        },
        "time_coverage": health.time_coverage,
        "date_fields": health.potential_date_fields,
        "geo_fields": health.potential_geographic_fields,
        "duplicate_rows": health.duplicate_rows,
        "total_missing": health.total_missing_values,
        "ambiguities": health.potential_ambiguities,
    }

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)

