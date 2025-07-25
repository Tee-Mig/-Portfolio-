import luigi
from pipeline.tasks.extract import ExtractData
from pipeline.tasks.transform import TransformData
from pipeline.tasks.convert_parquet import ConvertToParquet
from pipeline.tasks.load import LoadData

class ETLPipeline(luigi.WrapperTask):
    """
    Luigi pipeline that wraps the full ETL process:
    Extract -> Transform -> ConvertToParquet -> Load
    """
    def requires(self) -> luigi.Task:
        """
        Defines the dependency of this wrapper task.
        This pipeline ends with the LoadData task.
        """
        return LoadData()