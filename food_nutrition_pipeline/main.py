#! C:\Users\migue\AppData\Local\Programs\Python\Python312\python.exe

from pipeline.jobs.etl_pipeline import ETLPipeline
from pipeline.core.analysis import see_all_datas_on_db
import luigi

def main() -> int:
    luigi.build([ETLPipeline()], local_scheduler=True)
    see_all_datas_on_db()
    print("Fin")
    return 0


if __name__ == "__main__":
    main()