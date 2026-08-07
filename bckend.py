from fastapi import FastAPI

app = FastAPI(
    title="Context Engine",
    description="A deterministic, local-first data analysis engine.",
    version="0.1.0",
)


@app.get("/health")
def health_check():
    return {
        "status": "ok",
        "service": "context-engine",
        "version": "0.1.0",
    }
