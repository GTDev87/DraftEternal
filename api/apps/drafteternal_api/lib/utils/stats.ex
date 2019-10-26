defmodule DraftEternalApi.Web.Lib.Stats do
  def kr20(answer_key_matrix) do
    {n, k} = Matrix.size(answer_key_matrix)
    scores = Enum.map(answer_key_matrix, &Enum.sum/1)

    std = Statistics.stdev(scores)
    variance = std * std

    facility_sum =
      answer_key_matrix
      |> Matrix.transpose
      |> Enum.map(fn row ->
        facility = Statistics.mean(row)
        inverseFacility = 1 - facility
        facility * inverseFacility
      end)
      |> Enum.sum

    if (k > 1 && variance > 0),
      do: (k / (k - 1)) * (1 - (facility_sum / (variance * variance))),
      else: 0
  end

  def mastery_value(), do: 0.7
end
