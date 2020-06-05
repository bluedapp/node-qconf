export default qconf as {
  version(): string,
  getBatchKeys(path: string): string[],
  getBatchConf(path: string): Record<string, string>,
  getAllHost(path: string): string[],
  getHost(path: string): string,
  getConf(path: string): string
}
